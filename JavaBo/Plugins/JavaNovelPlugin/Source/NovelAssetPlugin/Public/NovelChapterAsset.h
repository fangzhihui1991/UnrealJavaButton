

#pragma once

#include "Core.h"
#include "UObject/NoExportTypes.h"
#include "NovelChapterAsset.generated.h"

class UNovelBasicBlock;
/**
 *
 */
UCLASS(Blueprintable,ClassGroup=JavaNovel)
class NOVELASSETPLUGIN_API UNovelChapterAsset : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TMap<FName,UNovelBasicBlock*> BasicBlocks;

	UFUNCTION(BlueprintCallable)
	UNovelBasicBlock* GetBasicBlockWithName(const FName& BlockName);

	// data that are required for reimport
#if WITH_EDITORONLY_DATA
	UPROPERTY(Category=ImportSettings,VisibleAnywhere,Instanced)
	UAssetImportData* AssetImportData;
#endif
};
