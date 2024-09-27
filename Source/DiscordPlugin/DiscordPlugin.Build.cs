// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DiscordPlugin : ModuleRules
{
	public DiscordPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
