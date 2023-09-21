// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Lobby/TPCharSelectUserWidget.h"
#include "GameMode/TPGameInstance.h"
#include "Components/TextBlock.h"

UTPCharSelectUserWidget::UTPCharSelectUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CharTypeBox = nullptr;
}


void UTPCharSelectUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

/*
Before: const UEnum* enumObject = FindObject(ANY_PACKAGE, TEXT(¡°ECustomEnum¡±));
After: const UEnum* enumObject = FindObject(nullptr, TEXT(¡°/Script/TPSGame.ECustomEnum¡±));
*/

	const UEnum* charStateEnum = FindObject<UEnum>(nullptr, TEXT("/Script/TeamProject.ECHARTYPE"), true);
	if (charStateEnum)
		CharType = charStateEnum->GetNameStringByValue((int64)SelectType);

	CharTypeBox->SetText(FText::FromString(CharType));
}

void UTPCharSelectUserWidget::UpdateType()
{
	UTPGameInstance* gameinst = Cast<UTPGameInstance>(GetGameInstance());

	gameinst->SetSelectCharType(SelectType);
}
