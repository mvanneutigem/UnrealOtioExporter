
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
#include "opentimelineio/track.h"
#include "opentimelineio/clip.h"
#include "opentimelineio/externalReference.h"

#include <string>


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
		FString MovieExtension = ".avi";

		//FOtioExporter* Exporter = new FOtioExporter;

		//TSharedRef<FMovieSceneTranslatorContext> ExportContext(new FMovieSceneTranslatorContext);
		//ExportContext->Init();

		const FMovieSceneExportMetadata& OutputMetadata = GetPipeline()->GetOutputMetadata();

		// otio export mess
		const UMovieSceneTrack* camera_cut_track = MovieScene->GetCameraCutTrack();
		const TArray <UMovieSceneTrack*> master_tracks = MovieScene->GetMasterTracks();

		// construct otio timeline
		auto movie_scene_name_fstring = FilePath;
		auto movie_scene_name = std::string(TCHAR_TO_UTF8(*movie_scene_name_fstring));

		opentimelineio::v1_0::Timeline* otio_timeline = new opentimelineio::v1_0::Timeline(
			movie_scene_name
		);

		opentimelineio::v1_0::Track* otio_master_track = new opentimelineio::v1_0::Track();

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
					// add the best format, maybe a fallback type thing like mov > jpeg > ...
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

					std::string clip_format_str = std::string(TCHAR_TO_UTF8(*clip_format));
					std::string FileName_Str = std::string(TCHAR_TO_UTF8(*FileName));
					std::string shot_display_name_str = std::string(TCHAR_TO_UTF8(*shot_display_name));
					opentimelineio::v1_0::Clip* otio_clip = new opentimelineio::v1_0::Clip(
						shot_display_name_str,
						new opentimelineio::v1_0::ExternalReference(FileName_Str)
					);

					opentimelineio::v1_0::ErrorStatus* error_status = nullptr;
					otio_master_track->append_child(otio_clip, error_status);
				}
			}

			// 
			
		}
		// UE_LOG(LogClass, Log, TEXT("Called FOtioExporter::Export camera_cut_track name: %s"), camera_cut_track->GetTrackName());


		//timeline->set_tracks(tracks);

		//// write out otio file
		//timeline->write_to(writer);

		// delete the timeline, which in turn is reponsible for deleting its children.
		//otio_master_track->possibly_delete();
		//otio_timeline->possibly_delete();


		// Log any messages in context
		//MovieSceneToolHelpers::MovieSceneTranslatorLogMessages(Exporter, ExportContext, false);

		//delete Exporter;
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