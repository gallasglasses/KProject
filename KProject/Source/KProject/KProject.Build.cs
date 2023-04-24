// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KProject : ModuleRules
{
	public KProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "SlateCore",
            "Slate" ,
            "GameplayTasks",
            "NavigationSystem",
            "QuestSystem"
        });

		PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "QuestSystem"
        });

		PublicIncludePaths.AddRange(new string[] 
		{ 
		    "KProject/Public/Player",
            "KProject/Public/Components",
            "KProject/Public/Damaging",
            "KProject/Public/UI",
            "KProject/Public/Menu",
            "KProject/Public/Menu/UI",
            "KProject/Public/Pickups",
            "KProject/Public/AI",
            "KProject/Public/AI/EQS",
            "KProject/Public/AI/Enemies/Animals",
            "KProject/Public/AI/Enemies/People",
            "KProject/Public/AI/Tasks",
            "KProject/Public/AI/Services",
            "KProject/Public/Weapons",
            "KProject/Public/Abilities",
            "KProject/Public/Sound",
            "KProject/Public/"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
