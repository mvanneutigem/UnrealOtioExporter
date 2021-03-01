#pragma once

#include "CoreMinimal.h"
#include "MoviePipelineOutputBase.h"
#include "MovieRenderPipelineDataTypes.h"
#include "OtioMoviePipelineSetting.generated.h"


UENUM(BlueprintType)
enum class OtioExportDataSource : uint8
{
	OutputMetadata,
	SequenceData
};

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
#if WITH_EDITOR
	virtual FText GetDisplayText() const override { 
		return NSLOCTEXT("MovieRenderPipeline", "OtioExporterDisplayName", "OTIO cut file"); 
	}
#endif
protected:
	virtual bool HasFinishedExportingImpl() const { return bHasFinishedExporting; }
	virtual void BeginExportImpl() override;

	bool EnsureWritableFile();
	bool bOverwriteFile;

public:
	/** What format string should the final files use? Can include folder prefixes, and format string ({sequence_name}, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")
		FString FileNameFormat;

	/** Whether to build the FCPXML from sequence data directly (for reimporting) or from actual frame output data (for post processing) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")
		OtioExportDataSource DataSource;

protected:
	/** The file to write to */
	FString FilePath;

	bool bHasFinishedExporting;
};
