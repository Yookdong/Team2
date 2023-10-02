// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerInfoWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

UPlayerInfoWidget::UPlayerInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CharIMG = nullptr;
	HPProgressBar = nullptr;
	OXProgressBar = nullptr;
}

void UPlayerInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerInfoWidget::SetHP(float current, float max)
{
	PerHP = current / max;
}

void UPlayerInfoWidget::SetOX(float current, float max)
{
	PerOX = current / max;
}