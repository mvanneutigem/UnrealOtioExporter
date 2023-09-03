// UE5 OTIO Movie Pipeline setting.
#include "OtioMoviePipelineSetting.h"
#include "MoviePipeline.h"
#include "MoviePipelineOutputSetting.h"
#include "MoviePipelineMasterConfig.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

#if WITH_EDITOR
#include "MovieSceneExportMetadata.h"
#include "MovieSceneToolHelpers.h"
#include "MovieScene.h"
#endif
#include "LevelSequence.h"

// For logs
#include "MovieRenderPipelineCoreModule.h"

//otio
#include "opentimelineio/timeline.h"
#include "opentimelineio/stack.h"
#include "opentimelineio/track.h"
#include "opentimelineio/clip.h"
#include "opentimelineio/externalReference.h"

#include <string>

namespace otio = opentimelineio::OPENTIMELINEIO_VERSION;

FString GetPreferredFormat(const TArray<FString>& Extensions)
{
	// Format extensions in order of preference
	const TArray<FString> PreferredFormats = {
		TEXT("MXF"),
		TEXT("MOV"),
		TEXT("AVI"),
		TEXT("EXR"),
		TEXT("PNG"),
		TEXT("JPEG"),
		TEXT("JPG")
	};

	for (const FString& Format : PreferredFormats)
	{
		if (Extensions.Contains(Format))
		{
			return Format;
		}
	}

	return Extensions[0]; // If we didn't find a preferred format, use the first one
}


void UMoviePipelineOtioExporter::BeginExportImpl()
{
	UE_LOG(LogMovieRenderPipeline, Log, TEXT("Running OtioMoviePipelineSetting OTIO export"));
	bHasFinishedExporting = true;

	UMoviePipelineOutputSetting* outputSetting = GetPipeline()->GetPipelineMasterConfig()->FindSetting<UMoviePipelineOutputSetting>();

	// Use our file name format ({sequence}), exposed on the setting gui, on the end of the shared common directory.
	FString fileNameFormatString = outputSetting->OutputDirectory.Path / FileNameFormat;

	TMap<FString, FString> formatOverrides;
	formatOverrides.Add(TEXT("ext"), TEXT("otio"));

	// Create a full output file path
	FMoviePipelineFormatArgs tempFormatArgs;
	GetPipeline()->ResolveFilenameFormatArguments(fileNameFormatString, formatOverrides, FilePath, tempFormatArgs);

	bool bSuccess = EnsureWritableFile();

	if (!bSuccess)
	{
		UE_LOG(LogMovieRenderPipeline, Error, TEXT("File not writable!"));
		return;
	}

	// gather neccesary data for export
	ULevelSequence* sequence = GetPipeline()->GetTargetSequence();
	
	UMovieScene* movieScene = sequence->GetMovieScene();
	if (!movieScene)
	{
		return;
	}

	UMovieSceneCinematicShotTrack* shotTrack = movieScene->FindMasterTrack<UMovieSceneCinematicShotTrack>();
	if (!shotTrack)
	{
		return;
	}
	
	int32 handleFrames = outputSetting->HandleFrameCount;
	const FMovieSceneExportMetadata& OutputMetadata = GetPipeline()->GetOutputMetadata();

	// construct otio timeline
	otio::ErrorStatus errorStatus;
	std::string masterSequenceName = std::string(TCHAR_TO_UTF8(*sequence->GetName()));

	// in unreal frames are stored based on the tick interval, and some functions give that value back, 
	// while others return the FPS frame number. We need the frame number in relation to the fps rate
	// so we convert these values in these instances.
	FFrameRate tickResolution = movieScene->GetTickResolution();
	FFrameRate displayRate = movieScene->GetDisplayRate();
	FFrameNumberRange playbackRange = movieScene->GetPlaybackRange();
	FFrameNumber duration = playbackRange.GetUpperBoundValue() - playbackRange.GetLowerBoundValue();
	float startTimeAsFloat = (float(playbackRange.GetLowerBoundValue().Value) / tickResolution.Numerator) * displayRate.Numerator;
	float durationAsFloat = duration.Value;
	float trackDurationAsFloat = (durationAsFloat / tickResolution.Numerator) * displayRate.Numerator;
	

	// we store the timeline in a container, if we dont do this we run into issues when trying to write out the file.
	otio::SerializableObject::Retainer<otio::Timeline> otioTimeline = otio::SerializableObject::Retainer<otio::Timeline>(
		new otio::Timeline(masterSequenceName, otio::RationalTime(startTimeAsFloat))
	);
	otio::TimeRange otioTrackTimerange = otio::TimeRange(
		otio::RationalTime(startTimeAsFloat, displayRate.AsDecimal()),
		otio::RationalTime(trackDurationAsFloat, displayRate.AsDecimal())
	);
	otio::Stack* otioStack = new otio::Stack("master", otioTrackTimerange);
	otio::Track* otioMasterTrack = new otio::Track("master", otioTrackTimerange);
	if (!otioStack->append_child(otioMasterTrack, &errorStatus))
	{
		FString error_message = UTF8_TO_TCHAR(
			(otio::ErrorStatus::outcome_to_string(errorStatus.outcome) + ": " + errorStatus.details).c_str()
		);
		UE_LOG(LogMovieRenderPipeline, Error, TEXT("OTIO Error: %s"), *error_message);
	}
	otioTimeline.value->set_tracks(otioStack);

	// UE4 to UE5 regression, Bug report Case # 00618138
	// the FMovieSceneExportMetadataShot objects in the FMovieSceneExportMetadata no longer contain MovieSceneShotSection info, the attribute it still there but it is a nullptr.
	// Due to the changes made here, specifically for the XML Exporter:
	// https://github.com/EpicGames/UnrealEngine/blob/5.3/Engine/Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Private/MoviePipeline.cpp#L261-L274
	// For now the functionality here mirrors the FCPXML plugin when OutputMetadata option is selected
	// With exception that it lays out the clips sequantially on the timeline rather than stacked.

	int currentFrame = startTimeAsFloat;
	int numberOfClips = 0;
	for (const FMovieSceneExportMetadataShot& Shot : OutputMetadata.Shots)
	{
		for (const TPair < FString, TMap<FString, FMovieSceneExportMetadataClip> >& Clip : Shot.Clips)
		{
			const TMap<FString, FMovieSceneExportMetadataClip>& ExtensionList = Clip.Value;
			if (ExtensionList.Num() > 0)
			{
				TArray<FString> Extensions;
				ExtensionList.GetKeys(Extensions);
				FString PreferredFormat = GetPreferredFormat(Extensions);
				check(ExtensionList.Contains(PreferredFormat));
				const FMovieSceneExportMetadataClip& ClipMetadata = ExtensionList[PreferredFormat];
				if (ClipMetadata.IsValid())
				{
					numberOfClips += 1;
					// Clip metadata
					int32 Duration = ClipMetadata.GetDuration();
					FString SectionName = Clip.Key;
					FString shotFilePath = ClipMetadata.FileName;

					// ClipMetadata.FileName is inconsistent, some formats pass full path, some only filename.
					FString outputDirectory = outputSetting->OutputDirectory.Path;
					
					FString* projectDir = tempFormatArgs.FilenameArguments.Find("project_dir");
					FStringFormatNamedArguments arguments;
					arguments.Add(TEXT("project_dir"), **projectDir);
					FString resolvedOutputDirectory = FString::Format(*outputDirectory, arguments);

					if (!shotFilePath.StartsWith(resolvedOutputDirectory)) {
						shotFilePath = resolvedOutputDirectory / shotFilePath;
					}
					shotFilePath = FString("file://") / shotFilePath;

					// construct otio clip
					std::string fileNameStr = std::string(TCHAR_TO_UTF8(*shotFilePath));
					std::string shotDisplayNameStr = std::string(TCHAR_TO_UTF8(*SectionName));
					shotDisplayNameStr += std::string("_clip") + std::to_string(numberOfClips);
					otio::ExternalReference* otioReference = new otio::ExternalReference(fileNameStr);
					otio::TimeRange otioMediaTimerange = otio::TimeRange(
						otio::RationalTime(currentFrame, displayRate.AsDecimal()),
						otio::RationalTime(Duration, displayRate.AsDecimal())
					);
					otioReference->set_available_range(otioMediaTimerange);

					otio::TimeRange otioClipTimerange = otio::TimeRange(
						otio::RationalTime(
							currentFrame,
							displayRate.AsDecimal()
						),
						otio::RationalTime(
							Duration,
							displayRate.AsDecimal()
						)
					);
					currentFrame += Duration;

					otio::Clip* otioClip = new otio::Clip(shotDisplayNameStr, otioReference, otioClipTimerange);
					// Add clip to timeline
					if (!otioMasterTrack->append_child(otioClip, &errorStatus))
					{
						FString errorMessage = UTF8_TO_TCHAR(
							(otio::ErrorStatus::outcome_to_string(errorStatus.outcome) + ": " + errorStatus.details).c_str()
						);
						UE_LOG(LogMovieRenderPipeline, Error, TEXT("OTIO Error: %s"), *errorMessage);
					}

				}
			}
		}
	}

	// For potential future "Sequencer" option - would not use any info from movie render queue export
	//const UMovieSceneSubTrack* SubTrack = Cast<const UMovieSceneSubTrack>(shotTrack);
	//if (SubTrack)
	//{
	//	for (UMovieSceneSection* Section : SubTrack->GetAllSections())
	//	{
	//		FMovieSceneFrameRange section_range = Section->SectionRange;
	//		TRange< FFrameNumber > meow = section_range.Value;
	//		UMovieSceneSubSection* SubSection = Cast<UMovieSceneSubSection>(Section);
	//		UMovieSceneSequence* SubSequence = SubSection ? SubSection->GetSequence() : nullptr;
	//		if (SubSequence && Section->IsActive())
	//		{
	//			UMovieSceneCinematicShotSection* ShotSection = Cast<UMovieSceneCinematicShotSection>(Section);
	//			FString DisplayString = ShotSection ? ShotSection->GetShotDisplayName() : SubSequence->GetName();
	//			// Add implementation here...
	//		}
	//	}
	//}


	// write out otio file
	std::string otioFilePathStr = std::string(TCHAR_TO_UTF8(*FilePath));
		
	if (!otioTimeline.value->to_json_file(otioFilePathStr, &errorStatus))
	{
		FString errorMessage = UTF8_TO_TCHAR(
			(otio::ErrorStatus::outcome_to_string(errorStatus.outcome) + ": " + errorStatus.details).c_str()
		);
		UE_LOG(LogMovieRenderPipeline, Error, TEXT("OTIO Error: %s"), *errorMessage);
	}

	// we take back ownership of the timeline so unreal's garbage collection can clean it up safely, 
	// if we dont do this or try to delete it ourselves with the "possibly_delete" function
	// we will end up with a heap corruption.
	otio::Timeline* timeline = otioTimeline.take_value();

	if (!bSuccess)
	{
		UE_LOG(LogMovieRenderPipeline, Error, TEXT("Failed to write otio cut file"));
	}
}


bool UMoviePipelineOtioExporter::EnsureWritableFile()
{
	FString directory = FPaths::GetPath(FilePath);

	if (!IFileManager::Get().DirectoryExists(*directory))
	{
		IFileManager::Get().MakeDirectory(*directory);
	}

	UMoviePipelineOutputSetting* outputSetting = GetPipeline()->GetPipelineMasterConfig()->FindSetting<UMoviePipelineOutputSetting>();

	// If the file doesn't exist, we're ok to continue
	if (IFileManager::Get().FileSize(*FilePath) == -1)
	{
		return true;
	}
	// If we're allowed to overwrite the file, and we deleted it ok, we can continue
	else if (outputSetting->bOverrideExistingOutput && FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*FilePath))
	{
		return true;
	}
	// We can't write to the file
	else
	{
		UE_LOG(
			LogMovieRenderPipeline, 
			Error, 
			TEXT("Failed to write otio cut file to '%s'. Should Overwrite: %d - If we should have overwritten the file, we failed to delete the file. If we shouldn't have overwritten the file the file already exists so we can't replace it."), 
			*FilePath, outputSetting->bOverrideExistingOutput
		);
		return false;
	}
}