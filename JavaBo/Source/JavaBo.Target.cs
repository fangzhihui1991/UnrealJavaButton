

using UnrealBuildTool;
using System.Collections.Generic;

public class JavaBoTarget : TargetRules
{
	public JavaBoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "JavaBo" } );
	}
}
