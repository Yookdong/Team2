// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Lobby/LobbyHUD.h"
#include "Blueprint/UserWidget.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	check(LobbyHudWidgetClass);

	LobbyHudWidget = CreateWidget<UUserWidget>(GetWorld(), LobbyHudWidgetClass);
	LobbyHudWidget->AddToViewport();

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeUIOnly());
		player0->bShowMouseCursor = true;
	}
}
