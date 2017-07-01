

#pragma once
#include "CoreMinimal.h"
#include "NovelInstruction.h"
#include "NovelClsInstruction.generated.h"

/**
 * Clear Screen Instruction
 */
UCLASS()
class NOVELASSETPLUGIN_API UNovelClsInstruction : public UNovelInstruction
{
	GENERATED_BODY()
public:
	UPROPERTY(Category=JavaNovel,VisibleAnywhere,BlueprintReadOnly)
	float TransitionDuration;

	// Easing parameters?
};
