// Copyright Epic Games, Inc. All Rights Reserved.

using System.Security.Cryptography.X509Certificates;
using UnrealBuildTool;

public class Caves_Taint : ModuleRules
{
	public Caves_Taint(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Voxel", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
		/*
		string RealSenseDirectory = Environment.GetEnvironmentVariable("RSSDK_DIR");
		string Platform = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "Win32";

		PublicIncludePaths.AddRange(new string[] {
			RealSenseDirectory + "include", RealSenseDirectory + "sample\\common\\include"
		});
		PublicAdditionalLibraries.Add(RealSenseDirectory + "lib\\" + Platform + "\\libpxc.lib");
		*/
	}
}
 