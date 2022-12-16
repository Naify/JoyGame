// JoyTest Game

using UnrealBuildTool;
using System.Collections.Generic;

public class JoyTestEditorTarget : TargetRules
{
	public JoyTestEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "JoyTest" } );
	}
}
