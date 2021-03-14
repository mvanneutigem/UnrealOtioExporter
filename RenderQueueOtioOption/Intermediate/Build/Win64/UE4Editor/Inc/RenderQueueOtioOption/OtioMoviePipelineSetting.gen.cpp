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
	RENDERQUEUEOTIOOPTION_API UClass* Z_Construct_UClass_UMoviePipelineOtioExporter_NoRegister();
	RENDERQUEUEOTIOOPTION_API UClass* Z_Construct_UClass_UMoviePipelineOtioExporter();
	MOVIERENDERPIPELINECORE_API UClass* Z_Construct_UClass_UMoviePipelineOutputBase();
	UPackage* Z_Construct_UPackage__Script_RenderQueueOtioOption();
// End Cross Module References
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
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMoviePipelineOtioExporter_Statics::NewProp_FileNameFormat,
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
	IMPLEMENT_CLASS(UMoviePipelineOtioExporter, 93120853);
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
