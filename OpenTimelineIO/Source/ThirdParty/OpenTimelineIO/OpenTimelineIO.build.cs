// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OpenTimelineIO : ModuleRules
{
	public OpenTimelineIO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
                "$(PluginDir)/Source/ThirdParty/OpenTimelineIO/include",
                "$(PluginDir)/Source/ThirdParty/OpenTimelineIO/include/Imath",
                "$(PluginDir)/Source/ThirdParty/OpenTimelineIO/include/opentimelineio/deps",
			 //   "$(PluginDir)/Source/ThirdParty/OpenTimelineIO/public_include",
				//"$(PluginDir)/Source/ThirdParty/OpenTimelineIO/public_include/Imath",
				//"$(PluginDir)/Source/ThirdParty/OpenTimelineIO/public_include/opentimelineio/deps",
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);


        if (Target.Platform == UnrealTargetPlatform.Win64)
        {

			//// Add the import library
			PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/OpenTimelineIO/opentimelineio.lib");
            PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/OpenTimelineIO/opentime.lib");
            PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/OpenTimelineIO/Imath-3_2.lib");


            //// Add runtime dependency
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/OpenTimelineIO/opentimelineio.dll");
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/OpenTimelineIO/opentime.dll");


            //// Delay-load the DLL
            PublicDelayLoadDLLs.Add("opentimelineio.dll");
            PublicDelayLoadDLLs.Add("opentime.dll");


        }
    }
}
