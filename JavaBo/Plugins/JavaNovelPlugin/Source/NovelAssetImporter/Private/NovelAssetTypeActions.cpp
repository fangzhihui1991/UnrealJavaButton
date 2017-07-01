#include "NovelAssetImporterPrivatePCH.h"
#include "NovelChapterAsset.h"
FText
FNovelAssetTypeActions::GetName() const{
	return NSLOCTEXT("AssetTypeActions","AssetTypeActions_NovelAsset", "Java Novel");
}
FColor
FNovelAssetTypeActions::GetTypeColor() const{
	return FColorList::Orange;
}
UClass*
FNovelAssetTypeActions::GetSupportedClass() const{
	return UNovelChapterAsset::StaticClass();
}
uint32
FNovelAssetTypeActions::GetCategories(){
	return EAssetTypeCategories::Media;
}
