// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RenderQueueOtioOption/Public/OtioMoviePipelineSetting.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOtioMoviePipelineSetting() {}
// Cross Module References
	RENDERQUEUEOTIOOPTION_API UEnum* Z_Construct_UEnum_RenderQueueOtioOption_OtioExportDataSource();
	UPackage* Z_Construct_UPackage__Script_RenderQueueOtioOption();
	RENDERQUEUEOTIOOPTION_API UClass* Z_Construct_UClass_UMoviePipelineOtioExporter_NoRegister();
	RENDERQUEUEOTIOOPTION_API UClass* Z_Construct_UClass_UMoviePipelineOtioExporter();
	MOVIERENDERPIPELINECORE_API UClass* Z_Construct_UClass_UMoviePipelineOutputBase();
// End Cross Module References
	static UEnum* OtioExportDataSource_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_RenderQueueOtioOption_OtioExportDataSource, Z_Construct_UPackage__Script_RenderQueueOtioOption(), TEXT("OtioExportDataSource"));
		}
		return Singleton;
	}
	template<> RENDERQUEUEOTIOOPTION_API UEnum* StaticEnum<OtioExportDataSource>()
	{
		return OtioExportDataSource_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_OtioExportDataSource(OtioExportDataSource_StaticEnum, TEXT("/Script/RenderQueueOtioOption"), TEXT("OtioExportDataSource"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_RenderQueueOtioOption_OtioExportDataSource_Hash() { return 1558337967U; }
	UEnum* Z_Construct_UEnum_RenderQueueOtioOption_OtioExportDataSource()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_RenderQueueOtioOption();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("OtioExportDataSource"), 0, Get_Z_Construct_UEnum_RenderQueueOtioOption_OtioExportDataSource_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "OtioExportDataSource::OutputMetadata", (int64)OtioExportDataSource::OutputMetadata },
				{ "OtioExportDataSource::SequenceData", (int64)OtioExportDataSource::SequenceData },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/OtioMoviePipelineSetting.h" },
				{ "OutputMetadata.Name", "OtioExportDataSource::OutputMetadata" },
				{ "SequenceData.Name", "OtioExportDataSource::SequenceData" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_RenderQueueOtioOption,
				nullptr,
				"OtioExportDataSource",
				"OtioExportDataSource",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void UMoviePipelineOtioExporter::StaticRegisterNativesUMoviePipelineOtioExporter()
	{
	}
	UClass* Z_Construct_UClass_UMoviePipelineOtioExporter_NoRegister()
	{
		return UMoviePipelineOtioExporter::StaticClass();
	}
	struct Z_Construct_UClass_UMoviePipelineOtioExporter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FileNameFormat_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FileNameFormat;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_DataSource_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DataSource_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_DataSource;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UMoviePipelineOutputBase,
		(UObject* (*)())Z_Construct_UPackage__Script_RenderQueueOtioOption,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "OtioMoviePipelineSetting.h" },
		{ "ModuleRelativePath", "Public/OtioMoviePipelineSetting.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_FileNameFormat_MetaData[] = {
		{ "Category", "File Output" },
		{ "Comment", "/** What format string should the final files use? Can include folder prefixes, and format string ({sequence_name}, etc.) */" },
		{ "ModuleRelativePath", "Public/OtioMoviePipelineSetting.h" },
		{ "ToolTip", "What format string should the final files use? Can include folder prefixes, and format string ({sequence_name}, etc.)" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_FileNameFormat = { "FileNameFormat", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UMoviePipelineOtioExporter, FileNameFormat), METADATA_PARAMS(Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_FileNameFormat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_FileNameFormat_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_DataSource_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_DataSource_MetaData[] = {
		{ "Category", "File Output" },
		{ "Comment", "/** Whether to build the FCPXML from sequence data directly (for reimporting) or from actual frame output data (for post processing) */" },
		{ "ModuleRelativePath", "Public/OtioMoviePipelineSetting.h" },
		{ "ToolTip", "Whether to build the FCPXML from sequence data directly (for reimporting) or from actual frame output data (for post processing)" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_DataSource = { "DataSource", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UMoviePipelineOtioExporter, DataSource), Z_Construct_UEnum_RenderQueueOtioOption_OtioExportDataSource, METADATA_PARAMS(Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_DataSource_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_DataSource_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_FileNameFormat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_DataSource_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_DataSource,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMoviePipelineOtioExporter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::ClassParams = {
		&UMoviePipelineOtioExporter::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMoviePipelineOtioExporter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UMoviePipelineOtioExporter, 704286474);
	template<> RENDERQUEUEOTIOOPTION_API UClass* StaticClass<UMoviePipelineOtioExporter>()
	{
		return UMoviePipelineOtioExporter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMoviePipelineOtioExporter(Z_Construct_UClass_UMoviePipelineOtioExporter, &UMoviePipelineOtioExporter::StaticClass, TEXT("/Script/RenderQueueOtioOption"), TEXT("UMoviePipelineOtioExporter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMoviePipelineOtioExporter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
