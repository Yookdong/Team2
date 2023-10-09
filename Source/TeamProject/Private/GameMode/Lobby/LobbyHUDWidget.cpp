// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Lobby/LobbyHUDWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "TPCharSelectUserWidget.h"


void ULobbyHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &ULobbyHUDWidget::StartGame);
	SelectButton->OnClicked.AddDynamic(this, &ULobbyHUDWidget::CharacterSelect);
	CancelButton->OnClicked.AddDynamic(this, &ULobbyHUDWidget::SelectCancel);

	CancelButton->SetVisibility(ESlateVisibility::Collapsed);
	StartButton->SetVisibility(ESlateVisibility::Collapsed);

	bIsSelectButton = false;
}

void ULobbyHUDWidget::StartGame()
{
	// 나중에 다른 제작 레벨로 바꿔야 됨
	GetWorld()->ServerTravel("MyMap3");
}

void ULobbyHUDWidget::CharacterSelect()
{
	CancelButton->SetVisibility(ESlateVisibility::Visible);
	SelectButton->SetVisibility(ESlateVisibility::Collapsed);
	SelectBox->SetVisibility(ESlateVisibility::HitTestInvisible);

	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc->HasAuthority())
	{
		StartButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void ULobbyHUDWidget::SelectCancel()
{
	SelectButton->SetVisibility(ESlateVisibility::Visible);
	CancelButton->SetVisibility(ESlateVisibility::Collapsed);
	SelectBox->SetVisibility(ESlateVisibility::Visible);

	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc->HasAuthority())
	{
		StartButton->SetVisibility(ESlateVisibility::Collapsed);
	}
}
