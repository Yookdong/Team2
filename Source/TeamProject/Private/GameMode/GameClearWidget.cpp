// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameClearWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameClearWidget::NativeConstruct()
{
	ReStartButton->OnClicked.AddDynamic(this, &UGameClearWidget::GameReStart);
	ExitButton->OnClicked.AddDynamic(this, &UGameClearWidget::GameExit);
}

void UGameClearWidget::GameReStart()
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc != nullptr)
	{
		GetWorld()->ServerTravel("Entry");
	}
}

void UGameClearWidget::GameExit()
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc != nullptr)
	{
		pc->ConsoleCommand("quit");
	}
}

