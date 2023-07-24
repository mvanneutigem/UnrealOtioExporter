
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


void UMoviePipelineOtioExporter::BeginExportImpl()
{
	UE_LOG(LogMovieRenderPipeline, Log, TEXT("Running OtioMoviePipelineSetting OTIO export"));
	bHasFinishedExporting = true;

	UMoviePipeline* pipeline = GetPipeline();
	UMoviePipelineExecutorJob* job = pipeline->GetCurrentJob();
	UMoviePipelineOutputSetting* outputSetting = pipeline->GetPipelineMasterConfig()->FindSetting<UMoviePipelineOutputSetting>();

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
	auto masterSequenceName = std::string(TCHAR_TO_UTF8(*sequence->GetName()));

	// in unreal frames are stored based on the tick interval, and some functions give that value back, 
	// while others return the FPS frame number. We ned the frame number in relation to the fps rate
	// so we convert these values in these instances.
	auto tickResolution = movieScene->GetTickResolution();
	auto displayRate = movieScene->GetDisplayRate();
	auto playbackRange = movieScene->GetPlaybackRange();
	auto startTime = (playbackRange.GetLowerBoundValue() / tickResolution.Numerator) * displayRate.Numerator;
	auto trackDuration = (playbackRange.GetUpperBoundValue() - playbackRange.GetLowerBoundValue()) / tickResolution.Numerator * displayRate.Numerator;

	// we store the timeline in a container, if we dont do this we run into issues when trying to write out the file.
	auto otioTimeline = otio::SerializableObject::Retainer<otio::Timeline>(
		new otio::Timeline(masterSequenceName, otio::RationalTime(startTime.Value / tickResolution.Numerator, displayRate.AsDecimal()))
	);
	auto otioTrackTimerange = otio::TimeRange(
		otio::RationalTime(startTime.Value, displayRate.AsDecimal()),
		otio::RationalTime(trackDuration.Value, displayRate.AsDecimal())
	);
	auto otioStack = new otio::Stack("master", otioTrackTimerange);
	auto otioMasterTrack = new otio::Track("master", otioTrackTimerange);
	if (!otioStack->append_child(otioMasterTrack, &errorStatus))
	{
		FString error_message = UTF8_TO_TCHAR(
			(otio::ErrorStatus::outcome_to_string(errorStatus.outcome) + ": " + errorStatus.details).c_str()
		);
		UE_LOG(LogMovieRenderPipeline, Error, TEXT("OTIO Error: %s"), *error_message);
	}
	otioTimeline.value->set_tracks(otioStack);

	for (int i = 0; i < OutputMetadata.Shots.Num(); i++)
	{
		FMovieSceneExportMetadataShot shot = OutputMetadata.Shots[i];
		FString shotDisplayName;
		FFrameNumberRange clipTimerange;
		otio::TimeRange otioClipTimerange;

		UMovieSceneCinematicShotSection* section = shot.MovieSceneShotSection.Get();

		if (section != nullptr) {
			clipTimerange = section->GetRange();
			UE_LOG(LogMovieRenderPipeline, Log, TEXT("Add shot to otio file: %s"), *section->GetShotDisplayName());
			shotDisplayName = section->GetShotDisplayName();
			otioClipTimerange = otio::TimeRange(
				otio::RationalTime(
					clipTimerange.GetLowerBoundValue().Value / tickResolution.Numerator * displayRate.Numerator,
					displayRate.AsDecimal()
				),
				otio::RationalTime(
					clipTimerange.GetUpperBoundValue().Value / tickResolution.Numerator * displayRate.Numerator,
					displayRate.AsDecimal()
				)
			);
		}

		for (auto& clip : shot.Clips)
		{
			FString clip_outer_name = clip.Key;
			for (auto& format : clip.Value)
			{
				if (FileReferenceFormat.Compare(format.Key, ESearchCase::IgnoreCase))
				{
					continue;
				}
				FString clipFormat = format.Key;
				FMovieSceneExportMetadataClip clipMetadata = format.Value;
				int32 duration = clipMetadata.GetDuration();
				int32 inFrame = handleFrames;
				FString shotFilePath = clipMetadata.FileName; // used to be just the filename, now is the entire path.
				if (section == nullptr)
				{
					auto index = shotFilePath.Find(FString("/"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
					shotDisplayName = shotFilePath.RightChop(index);
				}

				std::string fileNameStr = std::string(TCHAR_TO_UTF8(*shotFilePath));
				std::string shotDisplayNameStr = std::string(TCHAR_TO_UTF8(*shotDisplayName));

				auto otioReference = new otio::ExternalReference(fileNameStr);
				auto otioMediaTimerange = otio::TimeRange(
					otio::RationalTime(inFrame, displayRate.AsDecimal()), 
					otio::RationalTime(duration, displayRate.AsDecimal())
				);
				otioReference->set_available_range(otioMediaTimerange);

				if (section == nullptr)
				{
					otioClipTimerange = otio::TimeRange(
						otio::RationalTime(
							inFrame,
							displayRate.AsDecimal()
						),
						otio::RationalTime(
							inFrame + duration,
							displayRate.AsDecimal()
						)
					);
				}
				
				auto otioClip = new otio::Clip(shotDisplayNameStr, otioReference, otioClipTimerange);

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