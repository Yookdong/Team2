// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PauseWidget.h"
#include "Components/Button.h"

void UPauseWidget::NativeConstruct()
{
	KeyDescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);

	ResumetButton->OnClicked.AddDynamic(this, &UPauseWidget::Resume);
	KeyDescriptButton->OnClicked.AddDynamic(this, &UPauseWidget::KeyDescriptOpen);
	QuitGameButton->OnClicked.AddDynamic(this, &UPauseWidget::QuitGame);
}

void UPauseWidget::Resume()
{
}

void UPauseWidget::KeyDescriptOpen()
{
	KeyDescriptionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UPauseWidget::QuitGame()
{
}
