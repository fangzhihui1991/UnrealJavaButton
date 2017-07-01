using UnrealBuildTool;

public class JavaBo : ModuleRules
{
	public JavaBo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore",
			"NovelAssetPlugin"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		if(UEBuildConfiguration.bBuildEditor){
			PrivateDependencyModuleNames.Add("NovelAssetImporter");
		}
	}
}
