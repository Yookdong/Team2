// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPGameInstance.h"

UTPGameInstance::UTPGameInstance()
{
	bIsGameClear = false;
}

FST_Item* UTPGameInstance::GetItemRowData(FName name)
{
	return nullptr;
}

FST_Character* UTPGameInstance::GetCharacterRowData()
{
	if (CharacterData != nullptr)
	{
		return CharacterData->FindRow<FST_Character>(SetCharacterRowName(), TEXT(""));
	}

	return nullptr;
}

bool UTPGameInstance::SetUserName(FString name)
{
	if (name != FString() && name.Len() < 10)
	{
		UserName = name;
		return true;
	}

	return false;
}

FName UTPGameInstance::SetCharacterRowName()
{
	TArray<FName> names = CharacterData->GetRowNames();
	FName name;

	switch (SelectCharType)
	{
	case ECHARTYPE::White:
		name = names[0];
		break;
	case ECHARTYPE::Red:
		name = names[1];
		break;
	case ECHARTYPE::Green:
		name = names[2];
		break;
	case ECHARTYPE::Blue:
		name = names[3];
		break;
	default:
		return FName();
		break;
	}

	return name;
}

void UTPGameInstance::ReqSetIsClear_Implementation()
{
	ResSetIsClear();
}

void UTPGameInstance::ResSetIsClear_Implementation()
{
	bIsGameClear = true;
}
