

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NovelBasicBlock.generated.h"

class UNovelInstruction;
/**
 *
 */
UCLASS(Blueprintable,ClassGroup=JavaNovel)
class NOVELASSETPLUGIN_API UNovelBasicBlock : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(Category=JavaNovel,VisibleAnywhere,BlueprintReadOnly)
	TArray<UNovelInstruction*> Instructions;

};
