// Copyright Yang Dong

using UnrealBuildTool;

public class Aura : ModuleRules
{
	public Aura(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayAbilities", "AIModule", "MotionWarping", "TargetingSystem", "UMG", "PhysicsCore" });

		PrivateDependencyModuleNames.AddRange(new[]
			{ "EnhancedInput", "GameplayTags", "GameplayTags", "GameplayTasks", "NavigationSystem", "Niagara" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}