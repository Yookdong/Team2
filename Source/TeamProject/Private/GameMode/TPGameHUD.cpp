// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PlayHUDWidget.h"
#include "TPPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "TPGameModeBase.h"


void ATPGameHUD::BeginPlay()
{
	Super::BeginPlay();

	check(PlayHUDWidgetClass);

	PlayHUDWidget = CreateWidget<UPlayHUDWidget>(GetWorld(), PlayHUDWidgetClass);
	PlayHUDWidget->AddToViewport();

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeUIOnly());
	}

	BindPlayerState();
}

void ATPGameHUD::BindPlayerState()
{
	APlayerController* controller = GetWorld()->GetFirstPlayerController();

	if (IsValid(controller))
	{
		ATPPlayerState* tpstate = Cast<ATPPlayerState>(controller->PlayerState);

		if (IsValid(tpstate))
		{
			tpstate->Fuc_Dele_UpdateHP.AddDynamic(this, &ATPGameHUD::OnUpdateMyHP);
			OnUpdateMyHP(tpstate->CurrentHP, tpstate->MaxHP);

			tpstate->Fuc_Dele_UpdateOX.AddDynamic(this, &ATPGameHUD::OnUpdateMyOX);
			OnUpdateMyOX(tpstate->CurrentOX, tpstate->MaxOX);
		}
	}

	ATPGameModeBase* gamemode = Cast<ATPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (IsValid(gamemode))
	{
		gamemode->Fuc_Dele_UpdateTimer.AddDynamic(this, &ATPGameHUD::OnUpdateGameTime);
		OnUpdateGameTime(gamemode->Timer);
		
		return;
	}

	GetWorldTimerManager().SetTimer(TH_BindPlayerState, this, &ATPGameHUD::BindPlayerState, 0.1f, false);
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
	PlayHUDWidget->UpdateHP(curhp, maxhp);
}

void ATPGameHUD::OnUpdateMyOX_Implementation(float curox, float maxox)
{
	PlayHUDWidget->UpdateOX(curox, maxox);
}

void ATPGameHUD::OnUpdateGameTime_Implementation(float timer)
{
	PlayHUDWidget->UpdateTimer(timer);
}
