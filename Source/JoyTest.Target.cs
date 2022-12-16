// JoyTest Game

using UnrealBuildTool;
using System.Collections.Generic;

public class JoyTestTarget : TargetRules
{
	public JoyTestTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "JoyTest" } );
	}
}
