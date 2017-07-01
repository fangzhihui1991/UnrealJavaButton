#include "NovelAssetPluginPrivatePCH.h"

UNovelBasicBlock*
UNovelChapterAsset::GetBasicBlockWithName(const FName& BlockName){
	auto res=BasicBlocks.Find(BlockName);
	if(res){
		return *res;
	}else{
		UE_LOG(NovelAssetLog,Warning,TEXT("Undefined basic block specified: %s"),*BlockName.ToString());
		return nullptr;
	}
}
