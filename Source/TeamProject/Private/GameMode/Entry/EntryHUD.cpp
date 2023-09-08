// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Entry/EntryHUD.h"
#include "Blueprint/UserWidget.h"

void AEntryHUD::BeginPlay()
{
	Super::BeginPlay();

	check(EntryHudWidgetClass);

	EntryHudWidget = CreateWidget<UUserWidget>(GetWorld(), EntryHudWidgetClass);
	EntryHudWidget->AddToViewport();

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeUIOnly());
		player0->bShowMouseCursor = true;
	}
}
