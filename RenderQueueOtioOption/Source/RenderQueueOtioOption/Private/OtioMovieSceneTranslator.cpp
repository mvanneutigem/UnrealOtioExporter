
#include "OtioMovieSceneTranslator.h"
#include "MovieScene.h"
#include "MovieSceneTranslator.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "AssetData.h"
#include "LevelSequence.h"
#include "Tracks/MovieSceneAudioTrack.h"
#include "Sections/MovieSceneCinematicShotSection.h"
#include "Tracks/MovieSceneCinematicShotTrack.h"
#include "AssetRegistryModule.h"
//#include "XmlParser.h"

#define LOCTEXT_NAMESPACE "OtioMovieSceneTranslator"
//
///* MovieSceneCapture Otio Importer
//*****************************************************************************/
//
//FOtioImporter::FOtioImporter()
//	: FMovieSceneImporter()
//{
//}
//
//FOtioImporter::~FOtioImporter()
//{
//}
//
//FText FOtioImporter::GetFileTypeDescription() const
//{
//	return FText::FromString(TEXT("Otio (*.otio)|*.otio|"));
//}
//
//FText FOtioImporter::GetDialogTitle() const
//{
//	return LOCTEXT("ImportOtio", "Import otio timeline from...");
//}
//
//FText FOtioImporter::GetTransactionDescription() const
//{
//	return LOCTEXT("ImportOtioTransaction", "Import FCP 7 XML");
//}
//
//FName FOtioImporter::GetMessageLogWindowTitle() const
//{
//	return FName(TEXT("Otio Import"));
//}
//
//FText FOtioImporter::GetMessageLogLabel() const
//{
//	return LOCTEXT("OtioImportLogLabel", "Otio Import Log");
//}
//
//bool FOtioImporter::Import(UMovieScene* InMovieScene, FFrameRate InFrameRate, FString InFilename, TSharedRef<FMovieSceneTranslatorContext> InContext)
//{
//	// Create intermediate structure to assist with import
//	TSharedRef<FMovieSceneImportData> ImportData = MakeShared<FMovieSceneImportData>(InMovieScene, InContext);
//	if (!ImportData->IsImportDataValid())
//	{
//		return false;
//	}
//
//	// Load file to string
//	FString InString;
//	if (!FFileHelper::LoadFileToString(InString, *InFilename))
//	{
//		return false;
//	}
//
//	//// Construct XML from file string
//	//TSharedRef<FFCPXMLFile> FCPXMLFile = MakeShared<FFCPXMLFile>();
//	//bool bSuccess = FCPXMLFile->LoadFile(InString, EConstructMethod::ConstructFromBuffer);
//
//	//if (bSuccess && FCPXMLFile->IsValidFile())
//	//{
//	//	// Import the loaded Xml structure into the Sequencer movie scene
//	//	FFCPXMLImportVisitor ImportVisitor(ImportData, InContext);
//	//	bSuccess = FCPXMLFile->Accept(ImportVisitor);
//
//	//	// Flip rows
//	//	if (ImportData->GetCinematicMasterTrackData(false).IsValid())
//	//	{
//	//		int32 MaxVideoTrackRowIndex = ImportVisitor.GetMaxVideoTrackRowIndex();
//	//		for (TSharedPtr<FMovieSceneImportCinematicSectionData> SectionData : ImportData->GetCinematicMasterTrackData(false)->CinematicSections)
//	//		{
//	//			if (SectionData.IsValid())
//	//			{
//	//				UMovieSceneCinematicShotSection* CinematicSection = SectionData.Get()->CinematicSection;
//	//				if (CinematicSection)
//	//				{
//	//					CinematicSection->SetRowIndex(MaxVideoTrackRowIndex - CinematicSection->GetRowIndex());
//	//				}
//	//			}
//	//		}
//	//	}
//	//	if (ImportData->GetAudioMasterTrackData().IsValid())
//	//	{
//	//		int32 MaxAudioTrackRowIndex = ImportVisitor.GetMaxAudioTrackRowIndex();
//	//		for (TSharedPtr<FMovieSceneImportAudioSectionData> SectionData : ImportData->GetAudioMasterTrackData()->AudioSections)
//	//		{
//	//			if (SectionData.IsValid())
//	//			{
//	//				UMovieSceneAudioSection* AudioSection = SectionData.Get()->AudioSection;
//	//				if (AudioSection)
//	//				{
//	//					AudioSection->SetRowIndex(MaxAudioTrackRowIndex - AudioSection->GetRowIndex());
//	//				}
//	//			}
//	//		}
//	//	}
//	//}
//
//	//// add error message if one does not exist in the context
//	//if (!bSuccess && !InContext->ContainsMessageType(EMessageSeverity::Error))
//	//{
//	//	FText ErrorMessage = FCPXMLFile->GetLastError();
//	//	if (ErrorMessage.IsEmptyOrWhitespace())
//	//	{
//	//		ErrorMessage = LOCTEXT("FCPXMLImportGenericError", "Generic error occurred importing Final Cut Pro 7 XML file.");
//	//	}
//	//	InContext->AddMessage(EMessageSeverity::Error, ErrorMessage);
//	//}
//
//	//return bSuccess;
//	return false;
//}

/* MovieSceneCapture Otio Exporter
*****************************************************************************/

FOtioExporter::FOtioExporter()
	: FMovieSceneExporter()
{
}

FOtioExporter::~FOtioExporter()
{
}

FText FOtioExporter::GetFileTypeDescription() const
{
	return FText::FromString(TEXT("Otio (*.otio)|*.otio|"));
}

FText FOtioExporter::GetDialogTitle() const
{
	return LOCTEXT("ExportOtio", "Export Otio to...");
}

FText FOtioExporter::GetDefaultFileExtension() const
{
	return FText::FromString(TEXT("otio"));
}

FText FOtioExporter::GetNotificationExportFinished() const
{
	return LOCTEXT("OtioExportFinished", "Otio Export finished");
}

FText FOtioExporter::GetNotificationHyperlinkText() const
{
	return LOCTEXT("OpenOtioExportFolder", "Open Otio Export Folder...");
}

FName FOtioExporter::GetMessageLogWindowTitle() const
{
	return FName(TEXT("Otio Export"));
}

FText FOtioExporter::GetMessageLogLabel() const
{
	return LOCTEXT("OtioExportLogLabel", "Otio Export Log");
}

bool FOtioExporter::Export(
	const UMovieScene* InMovieScene, 
	FString InFilenameFormat, 
	FFrameRate InFrameRate, 
	uint32 InResX, 
	uint32 InResY, 
	int32 InHandleFrames, 
	FString InSaveFilename, 
	TSharedRef<FMovieSceneTranslatorContext> InContext, 
	FString InMovieExtension, 
	const FMovieSceneExportMetadata* InMetadata
)
{
	// add warning message if filename format is not "{shot}"
	FString AcceptedFormat = TEXT("{shot}");
	if (InFilenameFormat != AcceptedFormat)
	{
		InContext->AddMessage(
			EMessageSeverity::Warning,
			FText::Format(
				LOCTEXT(
					"OtioExportFilenameFormatWarning", 
					"Otio export expects rendered video sequences with filename format '{0}' but most recent rendered filename format is '{1}'."
				),
				FText::FromString(AcceptedFormat),
				FText::FromString(InFilenameFormat)
			)
		);
	}

	//// Construct XML from file string
	//TSharedRef<FFCPXMLFile> FCPXMLFile = MakeShared<FFCPXMLFile>();
	//FCPXMLFile->ConstructFile(FPaths::GetBaseFilename(InSaveFilename, true));

	//TSharedRef<FMovieSceneExportData> ExportData = MakeShared<FMovieSceneExportData>(InMovieScene, InFrameRate, InResX, InResY, InHandleFrames, InSaveFilename, InContext, InMovieExtension);

	//// Export sequencer movie scene, merging with existing Xml structure.
	//FFCPXMLExportVisitor* ExportVisitor;

	//if (InMetadata)
	//{
	//	ExportVisitor = new FFCPXMLMetadataExportVisitor(InSaveFilename, ExportData, InContext, InMetadata);
	//}
	//else
	//{
	//	ExportVisitor = new FFCPXMLExportVisitor(InSaveFilename, ExportData, InContext);
	//}

	//bool bSuccess = FCPXMLFile->Accept(*ExportVisitor);
	//if (bSuccess && FCPXMLFile->IsValidFile())
	//{
	//	// Save the Xml structure to a file
	//	bSuccess = FCPXMLFile->Save(InSaveFilename);
	//}

	//// add error message if one was not created during the visitor traversal
	//if (!bSuccess && !InContext->ContainsMessageType(EMessageSeverity::Error))
	//{
	//	FText Message = FCPXMLFile->GetLastError();
	//	if (Message.IsEmptyOrWhitespace())
	//	{
	//		Message = LOCTEXT("OtioExportGenericError", "Generic error occurred exporting Otio file.");
	//	}

	//	InContext->AddMessage(EMessageSeverity::Error, Message);
	//}

	//delete ExportVisitor;

	//return bSuccess;
	return false;
}

#undef LOCTEXT_NAMESPACE
