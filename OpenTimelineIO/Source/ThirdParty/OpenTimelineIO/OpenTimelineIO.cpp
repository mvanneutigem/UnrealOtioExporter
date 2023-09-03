// Copyright Epic Games, Inc. All Rights Reserved.

#include "OpenTimelineIO.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

//otio
#include "opentimelineio/timeline.h"
#include "opentimelineio/stack.h"
#include "opentimelineio/track.h"
#include "opentimelineio/clip.h"
#include "opentimelineio/externalReference.h"

#include <string>

namespace otio = opentimelineio::OPENTIMELINEIO_VERSION;

#define LOCTEXT_NAMESPACE "FOpenTimelineIOModule"

void FOpenTimelineIOModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("OpenTimelineIO")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/OpenTimelineIO/opentimelineio.dll"));

	opentimelineioLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (opentimelineioLibraryHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Succesfully loaded otio library"));
	}
	else {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load otio library"));
	}

}

void FOpenTimelineIOModule::DoSomething() {
	auto name = std::string("SomeName");

	auto newtimeline = otio::SerializableObject::Retainer<otio::Timeline>(new otio::Timeline(name));
}

void FOpenTimelineIOModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
    FPlatformProcess::FreeDllHandle(opentimelineioLibraryHandle);
	opentimelineioLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOpenTimelineIOModule, OpenTimelineIO)
