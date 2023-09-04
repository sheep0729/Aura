// Copyright Yang Dong

using UnrealBuildTool;

public class AuraTarget : TargetRules
{
	public AuraTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange( new[] { "Aura" } );
	}
}
