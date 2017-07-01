

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 *
 */
class NOVELASSETIMPORTER_API FNovelAssetTypeActions : public FAssetTypeActions_Base
{
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
	virtual bool IsImportedAsset() const override{return true;}
	virtual bool CanFilter() override{return true;}
};
