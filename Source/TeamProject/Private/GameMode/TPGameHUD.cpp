// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PlayHUDWidget.h"
#include "TPPlayerState.h"
#include "TPPlayerController.h"

void ATPGameHUD::BeginPlay()
{
	Super::BeginPlay();

	check(PlayHUDWidgetClass);

	PlayHUDWidget = CreateWidget<UPlayHUDWidget>(GetWorld(), PlayHUDWidgetClass);
	PlayHUDWidget->AddToViewport();

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeGameOnly());

		ATPPlayerController* ps = Cast<ATPPlayerController>(player0);

		if (ps != nullptr)
			ps->SetPlayHUDWidget(PlayHUDWidget);
	}
}

void ATPGameHUD::BindPlayerState(ATPPlayerState* tpstate)
{
	if (IsValid(tpstate))
	{
		tpstate->Fuc_Dele_UpdateHP.AddDynamic(this, &ATPGameHUD::OnUpdateMyHP);
		OnUpdateMyHP(tpstate->CurrentHP,tpstate->MaxHP);
	}
}

void ATPGameHUD::OpenInven()
{
	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeGameAndUI());
		PlayHUDWidget->OpenInven();
	}
}

void ATPGameHUD::CloseInven()
{
	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeGameOnly());
		PlayHUDWidget->CloseInven();
	}
}

void ATPGameHUD::OnUpdateMyHP_Implementation(float curhp, float maxhp)
{
}
