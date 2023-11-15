// Copyright Yang Dong

using System;
using UnrealBuildTool;

public class AuraEditor : ModuleRules
{
	public AuraEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine", 
				"EditorFramework",
				"UnrealEd",
				"PhysicsCore",
				"GameplayTagsEditor",
				"GameplayTasksEditor",
				"GameplayAbilities",
				"GameplayAbilitiesEditor",
				"AnimationModifierLibrary",
				"AnimationBlueprintLibrary",
				"AnimationModifiers",
				"Aura"
			});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
		});
	}
}