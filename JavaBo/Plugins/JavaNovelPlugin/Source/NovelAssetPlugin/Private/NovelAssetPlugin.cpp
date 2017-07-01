// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#include "NovelAssetPluginPrivatePCH.h"
#include "Modules/ModuleManager.h"
#include "INovelAssetPlugin.h"


class FNovelAssetPlugin : public INovelAssetPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FNovelAssetPlugin, NovelAssetPlugin )



void FNovelAssetPlugin::StartupModule()
{
	UE_LOG(NovelAssetLog,Log,TEXT("NovelAssetPlugin Loaded"));
}


void FNovelAssetPlugin::ShutdownModule()
{
	UE_LOG(NovelAssetLog,Log,TEXT("NovelAssetPlugin Shutdown"));
}

DEFINE_LOG_CATEGORY(NovelAssetLog);
