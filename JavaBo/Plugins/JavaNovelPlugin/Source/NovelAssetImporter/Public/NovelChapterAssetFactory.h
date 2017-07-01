

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EditorReimportHandler.h"
#include "NovelChapterAssetFactory.generated.h"

class UNovelChapterAsset;
class UNovelBasicBlock;
class FJsonValue;
/**
 *
 */
UCLASS()
class NOVELASSETIMPORTER_API UNovelChapterAssetFactory : public UFactory,public FReimportHandler
{
	GENERATED_BODY()
	UNovelChapterAssetFactory(const FObjectInitializer& ObjectInitializer);

	// UFactory interface
	virtual bool FactoryCanImport(const FString& Filename) override;
	FText GetToolTip() const override;
	virtual UObject* FactoryCreateText(UClass* InClass,UObject *InParent,FName InName,EObjectFlags Flags,UObject * Context,const TCHAR * Type,const TCHAR *& Buffer,const TCHAR * BufferEnd,FFeedbackContext * Warn) override;
	// End of UFactory interface

	// FReimportHandler interface
	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;
	virtual int32 GetPriority() const override;
	// End of FReimportHandler interface
private:
	TSharedPtr<FJsonObject> ParseJSON(const FString& FileContents,const FString& NameForErrors,bool bSilent=false);
	void DeserializeBasicBlocks(TSharedPtr<FJsonObject>& InJson,UNovelChapterAsset* OutAsset,EObjectFlags Flags);
	void DeserializeInstructions(TArray<TSharedPtr<FJsonValue> >& InJsonArray,UNovelBasicBlock* OutAsset,EObjectFlags Flags);
};
