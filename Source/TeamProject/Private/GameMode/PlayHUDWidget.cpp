// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlayHUDWidget.h"
#include "InventoryWidget.h"
#include "Character/PlayerInfoWidget.h"
#include "Components/TextBlock.h"
#include "GameOverWidget.h"
#include "GameClearWidget.h"


UPlayHUDWidget::UPlayHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UPlayHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ClearMissionNum = 0;

	InvenWidget->SetVisibility(ESlateVisibility::Collapsed);
	GameClearWidget->SetVisibility(ESlateVisibility::Collapsed);
	GameOverWidget->SetVisibility(ESlateVisibility::Collapsed);
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

void UPlayHUDWidget::OpenGameClear()
{
	GameClearWidget->SetVisibility(ESlateVisibility::Visible);

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeUIOnly());
		player0->bShowMouseCursor = true;
	}
}

void UPlayHUDWidget::OpenGameOver()
{
	GameOverWidget->SetVisibility(ESlateVisibility::Visible);

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeUIOnly());
		player0->bShowMouseCursor = true;
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

void UPlayHUDWidget::UpdateClearMissionNum(float clearnum)
{
	ClearMissionNum = clearnum;
}

// Client to Server
void UPlayHUDWidget::Req_UpdateTimer_Implementation(float time)
{
	Res_UpdateTimer(time);
}

// Server to Client
void UPlayHUDWidget::Res_UpdateTimer_Implementation(float time)
{
	UE_LOG(LogTemp, Display, TEXT("UpdateTimer"));
	int minute = 0;
	int second = 0;

	minute = time / 60.0f;
	second = (int)(time) % 60;

	FString timer = FString::Printf(TEXT("%d : %d"), minute, second);
	TimerText->SetText(FText::FromString(timer));
}
