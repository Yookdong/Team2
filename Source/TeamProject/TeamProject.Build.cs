// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TeamProject : ModuleRules
{
	public TeamProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "Paper2D", "GameplayTasks" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        // Include 시 경로를 생략

        PublicIncludePaths.AddRange(new string[] { "TeamProject", "TeamProject/Public", "TeamProject/Public/GameMode", "TeamProject/Public/Item", "TeamProject/Public/Character", "TeamProject/Public/GameMode/Entry", "TeamProject/Public/GameMode/Lobby", "TeamProject/Public/CY", "TeamProject/Public/BG", "TeamProject/Public/JH" });
        PrivateIncludePaths.AddRange(new string[] { "TeamProject/Private", "TeamProject/Private/GameMode", "TeamProject/Private/Item", "TeamProject/Private/Character", "TeamProject/Private/GameMode/Entry", "TeamProject/Private/GameMode/Lobby", "TeamProject/Private/CY", "TeamProject/Private/BG", "TeamProject/Private/JH" });
    }
}
