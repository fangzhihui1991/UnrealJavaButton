

#pragma once

#include "CoreMinimal.h"
#include "NovelInstruction.h"
#include "NovelTextInstruction.generated.h"

/**
 * Text instruction for novel
 */
UCLASS(Blueprintable,Category=JavaNovel)
class NOVELASSETPLUGIN_API UNovelTextInstruction : public UNovelInstruction
{
	GENERATED_BODY()
public:
	UPROPERTY(Category=JavaNovel,VisibleAnywhere,BlueprintReadOnly)
	FString TextContent;

	UPROPERTY(Category=JavaNovel,VisibleAnywhere,BlueprintReadOnly)
	float CharactersPerSecond;

	UPROPERTY(Category=JavaNovel,VisibleAnywhere,BlueprintReadOnly)
	bool AppendNewline;

	UPROPERTY(Category=JavaNovel,VisibleAnywhere,BlueprintReadOnly)
	bool AppendNewpage; // ページ送りのアイコンが変わるのでここにあると便利

};
