// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class KingdomOfEnoch : ModuleRules
{
	public KingdomOfEnoch(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Networking", "Sockets" });

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Slate", "SlateCore"
            // "GameplayAbilities", "GameplayTags", "GameplayTasks" // (enable later if you adopt GAS)
			});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
