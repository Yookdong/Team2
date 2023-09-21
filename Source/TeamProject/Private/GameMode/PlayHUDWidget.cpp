// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlayHUDWidget.h"
#include "InventoryWidget.h"
#include "Character/PlayerInfoWidget.h"
#include "Components/TextBlock.h"


UPlayHUDWidget::UPlayHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UPlayHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InvenWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UPlayHUDWidget::OpenInven()
{
	InvenWidget->OnUpdateInven();
	InvenWidget->SetVisibility(ESlateVisibility::Visible);

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeGameAndUI());
		player0->bShowMouseCursor = true;
	}
}

void UPlayHUDWidget::CloseInven()
{
	InvenWidget->SetVisibility(ESlateVisibility::Collapsed);

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeGameOnly());
		player0->bShowMouseCursor = false;
	}
}

void UPlayHUDWidget::UpdateHP(float current, float max)
{
	PlayerInfoWidget->SetHP(current, max);
}

void UPlayHUDWidget::UpdateOX(float current, float max)
{
	PlayerInfoWidget->SetOX(current, max);
}

void UPlayHUDWidget::UpdateTimer(float time)
{
	int minute = 0;
	int second = 0;

	minute = time / 60.0f;
	second = (int)(time) % 60;

	//FText::FromString(FText("mintue"))
}
