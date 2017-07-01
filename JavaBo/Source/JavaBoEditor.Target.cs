

using UnrealBuildTool;
using System.Collections.Generic;

public class JavaBoEditorTarget : TargetRules
{
	public JavaBoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "JavaBo" } );
	}
}
