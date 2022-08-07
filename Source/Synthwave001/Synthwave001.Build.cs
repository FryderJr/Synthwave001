// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Synthwave001 : ModuleRules
{
	public Synthwave001(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
