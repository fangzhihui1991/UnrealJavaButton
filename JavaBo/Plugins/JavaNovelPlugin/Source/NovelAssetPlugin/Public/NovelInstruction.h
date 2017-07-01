

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NovelInstruction.generated.h"

/**
 * Instruction base class for novel data
 * This can be an interface for now, but leave it an object, just in case.
 * We may need to add common features in the future.
 */
UCLASS(Blueprintable,Category=JavaNovel)
class NOVELASSETPLUGIN_API UNovelInstruction : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(Category=JavaNovel,VisibleAnywhere,BlueprintReadOnly)
	bool WaitUserClick;

	UPROPERTY(Category=JavaNovel,VisibleAnywhere,BlueprintReadOnly)
	bool Skippable;

};
