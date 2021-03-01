// REF: C:\Program Files\Epic Games\UE_4.26\Engine\Source\Editor\MovieSceneTools\Private\FCPXML

#pragma once

#include "CoreMinimal.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "MovieScene.h"
#include "MovieSceneTranslator.h"

class FMovieSceneTranslatorContext;
//
///**
// * The OtioImporter class is the entry point for launching an import of data from an Otio file into Sequencer.
// */
//class RENDERQUEUEOTIOOPTION_API FOtioImporter : public FMovieSceneImporter
//{
//public:
//	FOtioImporter();
//
//	virtual ~FOtioImporter();
//
//	/** Format description. */
//	virtual FText GetFileTypeDescription() const;
//	/** Import window title. */
//	virtual FText GetDialogTitle() const;
//	/** Scoped transaction description. */
//	virtual FText GetTransactionDescription() const;
//	/** Message log window title. */
//	virtual FName GetMessageLogWindowTitle() const;
//	/** Message log list label. */
//	virtual FText GetMessageLogLabel() const;
//
//public:
//	/*
//	 * Import Otio
//	 *
//	 * @param InMovieScene The movie scene to import the otio file into
//	 * @param InFrameRate The frame rate to import the otio at
//	 * @param InFilename The filename to import
//	 * @param OutError The return error message
//	 * @return Whether the import was successful
//	 */
//	bool Import(
//		UMovieScene* InMovieScene, 
//		FFrameRate InFrameRate, 
//		FString InFilename, 
//		TSharedRef<FMovieSceneTranslatorContext> InContext
//	);
//};

/**
 * The OtioExporter class is the entry point for launching an export of data from Sequencer into an XML file.
 */
class RENDERQUEUEOTIOOPTION_API FOtioExporter : public FMovieSceneExporter
{
public:
	/** Constructor */
	FOtioExporter();
	/** Destructor */
	virtual ~FOtioExporter();

	/** Format description. */
	virtual FText GetFileTypeDescription() const;
	/** Export dialog window title. */
	virtual FText GetDialogTitle() const;
	/** Default format file extension. */
	virtual FText GetDefaultFileExtension() const;
	/** Notification when export completes. */
	virtual FText GetNotificationExportFinished() const;
	/** Notification hyperlink to exported file path. */
	virtual FText GetNotificationHyperlinkText() const;
	/** Message log window title. */
	virtual FName GetMessageLogWindowTitle() const;
	/** Message log list label. */
	virtual FText GetMessageLogLabel() const;

public:
	/*
	 * Export otio
	 *
	 * @param InMovieScene The movie scene with the cinematic shot track and audio tracks to export
	 * @param InFilenameFormat The last filename format used to render shots.
	 * @param InFrameRate The frame rate for export.
	 * @param InResX Sequence resolution x.
	 * @param InResY Sequence resolution y.
	 * @param InHandleFrames The number of handle frames to include for each shot.
	 * @param InSaveFilename The file path to save to.
	 * @param OutError The return error message
	 * @param MovieExtension The movie extension for the shot filenames (ie. .avi, .mov, .mp4)
	 * @param InMetadata (optional) Metadata from export to override movie output file list
	 * @return Whether the export was successful
	 */

	virtual bool Export(
		const UMovieScene* InMovieScene, 
		FString InFilenameFormat, 
		FFrameRate InFrameRate, 
		uint32 InResX, 
		uint32 InResY, 
		int32 InHandleFrames, 
		FString InSaveFilename, 
		TSharedRef<FMovieSceneTranslatorContext> InContext, 
		FString InMovieExtension, 
		const FMovieSceneExportMetadata* InMetadata = nullptr
	);
};
