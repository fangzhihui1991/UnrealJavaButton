namespace UnrealBuildTool.Rules
{
	public class NovelAssetPlugin : ModuleRules
	{
		public NovelAssetPlugin(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					"NovelAssetPlugin/Public"
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"NovelAssetPlugin/Private"
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"Engine",
					"InputCore",
					"CoreUObject",
					"SlateCore",
					"AssetTools",
					"Slate"
				}
				);
			if(UEBuildConfiguration.bBuildEditor){
				PrivateDependencyModuleNames.Add("UnrealEd");
			}
		}
	}
}
