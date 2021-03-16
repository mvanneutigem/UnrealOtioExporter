
#include "OtioMoviePipelineSetting.h"
#include "MoviePipeline.h"
#include "MoviePipelineOutputSetting.h"
#include "MoviePipelineMasterConfig.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

#if WITH_EDITOR
//#include "MovieSceneTranslator.h"
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
	bHasFinishedExporting = true;

	UMoviePipeline* pipeline = GetPipeline();
	UMoviePipelineExecutorJob* job = pipeline->GetCurrentJob();
	UMoviePipelineOutputSetting* OutputSetting = pipeline->GetPipelineMasterConfig()->FindSetting<UMoviePipelineOutputSetting>();

	// Use our file name format ({sequence}), exposed on the setting gui, on the end of the shared common directory.
	FString FileNameFormatString = OutputSetting->OutputDirectory.Path / FileNameFormat;

	FStringFormatNamedArguments FormatOverrides;
	FormatOverrides.Add(TEXT("ext"), TEXT("otio"));

	// Create a full output file path
	FMoviePipelineFormatArgs TempFormatArgs;
	GetPipeline()->ResolveFilenameFormatArguments(FileNameFormatString, FormatOverrides, FilePath, TempFormatArgs);

	bool bSuccess = EnsureWritableFile();

	//otio::ErrorStatus* error_status = new otio::ErrorStatus();
	otio::ErrorStatus error_status;
	//std::shared_ptr<opentimelineio::v1_0::ErrorStatus> error_status = std::make_shared<opentimelineio::v1_0::ErrorStatus>();

	if (bSuccess)
	{
		UE_LOG(LogClass, Log, TEXT("Called FOtioExporter::Export -------------------------------------: %s"));
		// gather neccesary data for export
		ULevelSequence* Sequence = GetPipeline()->GetTargetSequence();
		UMovieScene* MovieScene = Sequence->GetMovieScene();
		if (!MovieScene)
		{
			return;
		}

		UMovieSceneCinematicShotTrack* ShotTrack = MovieScene->FindMasterTrack<UMovieSceneCinematicShotTrack>();
		if (!ShotTrack)
		{
			return;
		}

		FString FilenameFormat = OutputSetting->FileNameFormat;
		int32 HandleFrames = OutputSetting->HandleFrameCount;
		FFrameRate FrameRate = GetPipeline()->GetPipelineMasterConfig()->GetEffectiveFrameRate(Sequence);
		uint32 ResX = OutputSetting->OutputResolution.X;
		uint32 ResY = OutputSetting->OutputResolution.Y;

		const FMovieSceneExportMetadata& OutputMetadata = GetPipeline()->GetOutputMetadata();

		const UMovieSceneTrack* camera_cut_track = MovieScene->GetCameraCutTrack();
		const TArray <UMovieSceneTrack*> master_tracks = MovieScene->GetMasterTracks();

		// construct otio timeline
		auto movie_scene_name_fstring = FilePath;
		std::string movie_scene_name = std::string(TCHAR_TO_UTF8(*movie_scene_name_fstring));

		auto otio_timeline = otio::SerializableObject::Retainer<otio::Timeline>(new otio::Timeline(movie_scene_name));
		auto otio_stack = otio::SerializableObject::Retainer<otio::Stack>(new otio::Stack());
		auto otio_master_track = otio::SerializableObject::Retainer<otio::Track>(new otio::Track());

		for (int i = 0; i < OutputMetadata.Shots.Num(); i++)
		{
			FMovieSceneExportMetadataShot shot = OutputMetadata.Shots[i];

			UMovieSceneCinematicShotSection* section = shot.MovieSceneShotSection.Get();

			UE_LOG(LogClass, Log, TEXT("Called FOtioExporter::Export shot display name: %s"), *section->GetShotDisplayName());
			FString shot_display_name = section->GetShotDisplayName();

			for (auto& clip : shot.Clips)
			{
				FString clip_outer_name = clip.Key;
				UE_LOG(LogClass, Log, TEXT("Called FOtioExporter::Export clip_outer_name: %s"), *clip_outer_name);
				for (auto& format : clip.Value)
				{
					// add the best format only, maybe a fallback type thing like mov > jpeg > ...
					FString clip_format = format.Key;
					FMovieSceneExportMetadataClip clipmetadata = format.Value;
					int32 Duration = clipmetadata.GetDuration();
					int32 StartFrame = clipmetadata.StartFrame;
					int32 EndFrame = clipmetadata.EndFrame;
					int32 InFrame = HandleFrames;
					int32 OutFrame = InFrame + Duration;
					FString FileName = clipmetadata.FileName;

					UE_LOG(LogClass, Log, TEXT("Called FOtioExporter::Export clip_format: %s"), *clip_format);
					UE_LOG(LogClass, Log, TEXT("Called FOtioExporter::Export clip FileName: %s"), *FileName);

					FString ShotFilePath = OutputSetting->OutputDirectory.Path / FileName;
					UE_LOG(LogClass, Log, TEXT("Called FOtioExporter::Export ShotFilePath: %s"), *ShotFilePath);

					std::string clip_format_str = std::string(TCHAR_TO_UTF8(*clip_format));
					std::string FileName_Str = std::string(TCHAR_TO_UTF8(*ShotFilePath));
					std::string shot_display_name_str = std::string(TCHAR_TO_UTF8(*shot_display_name));
					std::string shot_File_path_Str = std::string(TCHAR_TO_UTF8(*ShotFilePath));

					// TODO: memory management...
					auto otio_reference = otio::SerializableObject::Retainer<otio::ExternalReference>(
						new otio::ExternalReference(FileName_Str)
					);

					auto otio_clip_timerange = otio::TimeRange(otio::RationalTime(InFrame), otio::RationalTime(Duration));
					auto otio_clip = otio::SerializableObject::Retainer<otio::Clip>(
						new otio::Clip(shot_File_path_Str, otio_reference, otio_clip_timerange)
					);

					if (!otio_master_track.value->append_child(otio_clip, &error_status))
					{
						FString error_message = UTF8_TO_TCHAR(
							(otio::ErrorStatus::outcome_to_string(error_status.outcome) + ": " + error_status.details).c_str()
						);
						UE_LOG(LogMovieRenderPipeline, Error, TEXT("OTIO Error: %s"), *error_message);
					}

					// TODO: add all the data to the clip :)
				}
			}
			
		}

		if (!otio_stack.value->append_child(otio_master_track, &error_status))
		{
			FString error_message = UTF8_TO_TCHAR(
				(otio::ErrorStatus::outcome_to_string(error_status.outcome) + ": " + error_status.details).c_str()
			);
			UE_LOG(LogMovieRenderPipeline, Error, TEXT("OTIO Error: %s"), *error_message);
		}
		otio_timeline.value->set_tracks(otio_stack);

		// write out otio file
		std::string otio_file_path_str = std::string(TCHAR_TO_UTF8(*FilePath));
		
		// bad heap, this falls over on the Clip destructor where it calls managed_release :(
		if (!otio_timeline.value->to_json_file(otio_file_path_str, &error_status))
		{
			FString error_message = UTF8_TO_TCHAR(
				(otio::ErrorStatus::outcome_to_string(error_status.outcome) + ": " + error_status.details).c_str()
			);
			UE_LOG(LogMovieRenderPipeline, Error, TEXT("OTIO Error: %s"), *error_message);
		}

		// delete the timeline, which in turn is reponsible for deleting its children.
		// this crashes same as the above :(
		otio_timeline.value->possibly_delete();
	}

	if (!bSuccess)
	{
		UE_LOG(LogMovieRenderPipeline, Error, TEXT("Failed to write otio cut file"));
	}

}


bool UMoviePipelineOtioExporter::EnsureWritableFile()
{
	FString Directory = FPaths::GetPath(FilePath);

	if (!IFileManager::Get().DirectoryExists(*Directory))
	{
		IFileManager::Get().MakeDirectory(*Directory);
	}

	UMoviePipelineOutputSetting* OutputSetting = GetPipeline()->GetPipelineMasterConfig()->FindSetting<UMoviePipelineOutputSetting>();

	// If the file doesn't exist, we're ok to continue
	if (IFileManager::Get().FileSize(*FilePath) == -1)
	{
		return true;
	}
	// If we're allowed to overwrite the file, and we deleted it ok, we can continue
	else if (OutputSetting->bOverrideExistingOutput && FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*FilePath))
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
			*FilePath, OutputSetting->bOverrideExistingOutput
		);
		return false;
	}
}