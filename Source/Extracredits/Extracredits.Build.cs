// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Extracredits : ModuleRules
{
	public Extracredits(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "ApplicationCore", "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
