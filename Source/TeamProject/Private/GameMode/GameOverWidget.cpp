// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	ReStartButton->OnClicked.AddDynamic(this, &UGameOverWidget::GameReStart);
	ExitButton->OnClicked.AddDynamic(this, &UGameOverWidget::GameExit);
}

void UGameOverWidget::GameReStart()
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc != nullptr)
	{
		GetWorld()->ServerTravel("Entry");
	}
}

void UGameOverWidget::GameExit()
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc != nullptr)
	{
		pc->ConsoleCommand("quit");
	}
}
