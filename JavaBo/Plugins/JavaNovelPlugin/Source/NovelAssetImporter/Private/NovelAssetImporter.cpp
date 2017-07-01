#include "NovelAssetImporterPrivatePCH.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "INovelAssetImporter.h"
#include "AssetToolsModule.h"

class FNovelAssetImporter : public INovelAssetImporter
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	/** The collection of registered asset type actions. */
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;
};

IMPLEMENT_MODULE( FNovelAssetImporter, NovelAssetImporter )

void FNovelAssetImporter::StartupModule()
{
	// Register asset types
	auto& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	auto NovelAssetTypeActions=MakeShareable(new FNovelAssetTypeActions);
	AssetTools.RegisterAssetTypeActions(NovelAssetTypeActions);
	RegisteredAssetTypeActions.Emplace(NovelAssetTypeActions);
	UE_LOG(NovelImporterLog,Log,TEXT("NovelImporter loaded"));
}


void FNovelAssetImporter::ShutdownModule()
{
	auto AssetToolsModule=FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	if(AssetToolsModule){
		auto& AssetTools=AssetToolsModule->Get();
		for(auto Action: RegisteredAssetTypeActions){
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
	UE_LOG(NovelImporterLog,Log,TEXT("NovelImporter Shutdown"));
}

DEFINE_LOG_CATEGORY(NovelImporterLog);
