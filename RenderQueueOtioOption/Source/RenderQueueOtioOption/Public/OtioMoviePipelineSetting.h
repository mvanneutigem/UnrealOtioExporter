#pragma once

#include "CoreMinimal.h"
#include "MoviePipelineOutputBase.h"
#include "MovieRenderPipelineDataTypes.h"
#include "OtioMoviePipelineSetting.generated.h"


UCLASS(BlueprintType)
class RENDERQUEUEOTIOOPTION_API UMoviePipelineOtioExporter : public UMoviePipelineOutputBase
{
	GENERATED_BODY()
public:
	UMoviePipelineOtioExporter()
		: FileNameFormat(TEXT("{sequence_name}"))
		, bHasFinishedExporting(false)
	{}

public:
	virtual FText GetDisplayText() const override { 
		return NSLOCTEXT("MovieRenderPipeline", "OtioExporterDisplayName", "OTIO cut file"); 
	}
protected:
	virtual bool HasFinishedExportingImpl() const { return bHasFinishedExporting; }
	virtual void BeginExportImpl() override;

	bool EnsureWritableFile();
	bool bOverwriteFile;

public:
	/** What format string should the final files use? Can include folder prefixes, and format string ({sequence_name}, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTimelineIO Setting")
		FString FileNameFormat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTimelineIO Setting")
		FString FileReferenceFormat = "jpeg";

protected:
	/** The file to write to */
	FString FilePath;

	bool bHasFinishedExporting;
};

