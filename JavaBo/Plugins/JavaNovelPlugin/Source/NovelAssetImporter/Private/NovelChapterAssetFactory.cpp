#define LOCTEXT_NAMESPACE "NovelFactory"
#include "NovelAssetImporterPrivatePCH.h"
#include "NovelChapterAsset.h"
#include "NovelBasicBlock.h"
#include "NovelTextInstruction.h"
#include "NovelClsInstruction.h"
#include "Editor.h"
#include "EditorFramework/AssetImportData.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

UNovelChapterAssetFactory::UNovelChapterAssetFactory(const FObjectInitializer& ObjectInitializer){
	bCreateNew=false;
	bEditAfterNew=false;
	bText=true;
	bEditorImport=true;
	Formats.Add(TEXT("javason;Java Novel JSON file"));
	SupportedClass=UNovelChapterAsset::StaticClass();
}
// UFactory interface
bool
UNovelChapterAssetFactory::FactoryCanImport(const FString& Filename){
	return Filename.EndsWith(".javason",ESearchCase::IgnoreCase);
}
FText
UNovelChapterAssetFactory::GetToolTip() const{
	return LOCTEXT("JavaNovelFactoryToolTip","Java Novel JSON file");
}
UObject*
UNovelChapterAssetFactory::FactoryCreateText(UClass* InClass,UObject *InParent,FName InName,EObjectFlags Flags,UObject * Context,const TCHAR * Type,const TCHAR *& Buffer,const TCHAR * BufferEnd,FFeedbackContext * Warn){
	Flags |= RF_Transactional;
	FEditorDelegates::OnAssetPreImport.Broadcast(this,InClass,InParent,InName,Type);

	const FString NameForErrors(InName.ToString());
	const FString FileContent(BufferEnd-Buffer,Buffer);
	auto NovelJSON=ParseJSON(FileContent,NameForErrors);
	UNovelChapterAsset* Result=nullptr;
	if(NovelJSON.IsValid()){
		Result=NewObject<UNovelChapterAsset>(InParent,InName,Flags);
		Result->Modify();
		DeserializeBasicBlocks(NovelJSON,Result,Flags);
		Result->PostEditChange();

		// Initialize data for Reimport
		auto ImportData=NewObject<UAssetImportData>(Result,NAME_None,RF_NoFlags);
		ImportData->Update(CurrentFilename);
		Result->AssetImportData=ImportData;
	}else{
		UE_LOG(NovelImporterLog,Log,TEXT("Invalid JSON"));
	}
	FEditorDelegates::OnAssetPostImport.Broadcast(this, Result);
	return Result;
}
// End of UFactory interface
void
UNovelChapterAssetFactory::DeserializeBasicBlocks(TSharedPtr<FJsonObject>& InJson,UNovelChapterAsset* OutAsset,EObjectFlags Flags){
	for(auto& pair:InJson->Values){
		FName BasicBlockName(*pair.Key);
		auto BasicBlock=NewObject<UNovelBasicBlock>(OutAsset,BasicBlockName,Flags);
		BasicBlock->Modify();
		auto BasicBlockJson=pair.Value->AsArray();
		DeserializeInstructions(BasicBlockJson,BasicBlock,Flags);
		BasicBlock->PostEditChange();
		OutAsset->BasicBlocks.Emplace(BasicBlockName,BasicBlock);
	}
}
void
UNovelChapterAssetFactory::DeserializeInstructions(TArray<TSharedPtr<FJsonValue> >& InJsonArray,UNovelBasicBlock* OutAsset,EObjectFlags Flags){
	for(auto& InstructionJsonVal: InJsonArray){
		auto InstObj=InstructionJsonVal->AsObject();
		if(!InstObj->HasTypedField<EJson::String>(TEXT("op"))){continue;}
		auto OpString=InstObj->GetStringField(TEXT("op"));
		if(OpString==TEXT("text")){
			auto TextInsn=NewObject<UNovelTextInstruction>(OutAsset,NAME_None,Flags);
			TextInsn->Modify();
			TextInsn->TextContent=InstObj->GetStringField(TEXT("TextContent"));
			TextInsn->PostEditChange();
			OutAsset->Instructions.Emplace(TextInsn);
		}else if(OpString==TEXT("cls")){
			auto ClsInsn=NewObject<UNovelClsInstruction>(OutAsset,NAME_None,Flags);
			OutAsset->Instructions.Emplace(ClsInsn);
		}
	}
}
TSharedPtr<FJsonObject>
UNovelChapterAssetFactory::ParseJSON(const FString& FileContents,const FString& NameForErrors,bool bSilent){
	if(FileContents.IsEmpty()){
		if(!bSilent){
			UE_LOG(NovelImporterLog,Log,TEXT("Novel JSON file '%s' is empty."),*NameForErrors);
		}
		return nullptr;
	}else{
		const auto& Reader=TJsonReaderFactory<>::Create(FileContents);
		TSharedPtr<FJsonObject> DescriptorObject;
		if(FJsonSerializer::Deserialize(Reader,DescriptorObject)&&DescriptorObject.IsValid()){
			return DescriptorObject;
		}else{
			UE_LOG(NovelImporterLog,Log,TEXT("Failed to parse novel JSON file '%s'. Error: '%s'"),*NameForErrors,*Reader->GetErrorMessage());
			return nullptr;
		}
	}
}

// FReimportHandler interface
bool
UNovelChapterAssetFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames){
	if(auto ChapterAsset=Cast<UNovelChapterAsset>(Obj)){
		if(ChapterAsset->AssetImportData){
			ChapterAsset->AssetImportData->ExtractFilenames(OutFilenames);
		}else{
			OutFilenames.Emplace(FString());
		}
		return true;
	}
	return false;
}
void
UNovelChapterAssetFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths){
	if(auto ChapterAsset=Cast<UNovelChapterAsset>(Obj)){
		if(ensure(NewReimportPaths.Num()==1)){
			auto ImportData=ChapterAsset->AssetImportData;
			ImportData->UpdateFilenameOnly(NewReimportPaths[0]);
		}
	}
}
EReimportResult::Type
UNovelChapterAssetFactory::Reimport(UObject* Obj){
	if(auto ChapterAsset=Cast<UNovelChapterAsset>(Obj)){
		CurrentFilename=ChapterAsset->AssetImportData->GetFirstFilename();
		auto OutCancelled=false;
		auto NewObj=ImportObject(UNovelChapterAsset::StaticClass(),Obj->GetOuter(),*Obj->GetName(),RF_Public | RF_Standalone, CurrentFilename, nullptr, OutCancelled);
		if(OutCancelled){
			return EReimportResult::Cancelled;
		}else if(NewObj){
			Obj=NewObj;
			return EReimportResult::Succeeded;
		}
	}
	return EReimportResult::Failed;
}
int32
UNovelChapterAssetFactory::GetPriority() const{
	return ImportPriority;
}
// End of FReimportHandler interface
