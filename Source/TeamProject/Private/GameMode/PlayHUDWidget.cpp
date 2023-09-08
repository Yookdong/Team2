// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlayHUDWidget.h"
#include "InventoryWidget.h"


void UPlayHUDWidget::OpenInven()
{
	InvenWidget->UpdateInven();
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
