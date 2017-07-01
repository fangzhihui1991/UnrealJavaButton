namespace UnrealBuildTool.Rules
{
	public class NovelAssetImporter : ModuleRules
	{
		public NovelAssetImporter(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					"NovelAssetImporter/Public"
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"NovelAssetImporter/Private"
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"Engine",
					"CoreUObject",
					"Json",
					"NovelAssetPlugin"
				}
				);
			if(UEBuildConfiguration.bBuildEditor){
				PrivateDependencyModuleNames.Add("UnrealEd");
			}
		}
	}
}
