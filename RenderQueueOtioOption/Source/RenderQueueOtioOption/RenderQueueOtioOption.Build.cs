// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RenderQueueOtioOption : ModuleRules
{
	public RenderQueueOtioOption(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
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
                "Projects",
                "MovieRenderPipelineCore",
                "MovieSceneTools",
                "MovieSceneTracks",
                "LevelSequence",
                "MovieScene"
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
        
         //      Type = ModuleType.External;

		//if (Target.Platform == UnrealTargetPlatform.Win64)
		//{
		//	// Add the import library
		//	PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/opentimelineio/x64/Release/opentimelineio.lib");

		//	// Delay-load the DLL, so we can load it from the right place first
		//	PublicDelayLoadDLLs.Add("opentimelineio.dll");

		//	// Ensure that the DLL is staged along with the executable
		//	RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/opentimelineio/x64/Release/opentimelineio.dll");
        //      }
	}
}
