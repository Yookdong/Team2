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

	UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECHARTYPE"), true);
	if (CharStateEnum)
		CharType = CharStateEnum->GetNameStringByValue((int64)SelectType);

	CharTypeBox->Text = FText::FromString(CharType);
}

void UTPCharSelectUserWidget::UpdateType()
{
	UTPGameInstance* gameinst = Cast<UTPGameInstance>(GetGameInstance());

	gameinst->SetSelectCharType(SelectType);
}
