// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPGameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "TPPlayerController.h"
#include "GameMode/TPGameInstance.h"

ATPGameModeBase::ATPGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ClearMissionNum = 0;
	MaxMission = 5;
	CurrentCharNum = 0;
	MaxTimer = 1200.0f;
	Timer = MaxTimer;
	bIsStart = false;
	bIsBindClear = false;
}

void ATPGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPGameModeBase, Timer);
	DOREPLIFETIME(ATPGameModeBase, ClearMissionNum);
}

void ATPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	BindFunction();
}

void ATPGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Timer <= 0 || (CurrentCharNum == GetWorld()->GetNumPlayerControllers()))
	{
		UE_LOG(LogTemp, Display, TEXT("GameOver"));
		GetWorld()->ServerTravel("Ending");
	}

	if (ClearMissionNum == MaxMission)
	{
		UE_LOG(LogTemp, Display, TEXT("GameClear"));

		UTPGameInstance* gameinst = Cast<UTPGameInstance>(GetGameInstance());

		if (gameinst != nullptr)
		{
			gameinst->ReqSetIsClear();
			GetWorld()->ServerTravel("Ending");
		}
	}

	if (bIsStart)
	{
		UE_LOG(LogTemp, Display, TEXT("Start Timer Tick"));
		Req_PassedTime(DeltaSeconds);
	}

	if (bIsBindClear)
	{
		GetWorldTimerManager().ClearTimer(TH_UpdateTimer);
		bIsBindClear = false;
	}
}

void ATPGameModeBase::BindFunction()
{
	UpdateTimer(Timer);
}


void ATPGameModeBase::OnRep_Timer()
{
	UE_LOG(LogTemp, Display, TEXT("OnRep_Timer"));
	if (Fuc_Dele_UpdateTimer.IsBound())
		Fuc_Dele_UpdateTimer.Broadcast(Timer);
}

void ATPGameModeBase::OnRep_ClearMission()
{
	UE_LOG(LogTemp, Display, TEXT("OnRep_ClearMission"));
	if (Fuc_Dele_UpdateClearMissionNum.IsBound())
		Fuc_Dele_UpdateClearMissionNum.Broadcast(ClearMissionNum);
}

void ATPGameModeBase::UpdateTimer(float newtime)
{
	//int32 num = 0;

	////Find All PC
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		UE_LOG(LogTemp, Display, TEXT("for by UpdateTimer"));
		ATPPlayerController* PC = Cast<ATPPlayerController>(*Iter);
		if (PC)
		{
			UE_LOG(LogTemp, Display, TEXT("CastController"));
			PC->UpdateTimer(Timer);
			//num++;
		}
	}

	if (HasAuthority())
	{
		//Timer = newtime;
		OnRep_Timer();
	}

	//if (num == GetWorld()->GetNumPlayerControllers())
	//{
	//	bIsBindClear = true;
	//	return;
	//}

	//GetWorldTimerManager().SetTimer(TH_UpdateTimer, this, &ATPGameModeBase::BindFunction, 0.1f, false);
}

// Client to Server
void ATPGameModeBase::Req_StartTimer_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("Req_StartTimer"));
	Res_StartTimer();
}

void ATPGameModeBase::Req_PassedTime_Implementation(float time)
{
	UE_LOG(LogTemp, Display, TEXT("Req_PassedTime"));
	Res_PassedTime(time);
}

void ATPGameModeBase::Req_UpdateClearMissionNum_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("Req_UpdateClearMissionNum"));
	ReS_UpdateClearMissionNum();
}

// Server to Client
void ATPGameModeBase::Res_StartTimer_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("Res_StartTimer"));
	bIsStart = !bIsStart;
}

void ATPGameModeBase::Res_PassedTime_Implementation(float time)
{
	UE_LOG(LogTemp, Display, TEXT("Res_PassedTime"));
	Timer -= time;

	Timer = FMath::Clamp(Timer, 0, MaxTimer);

	OnRep_Timer();
	//UpdateTimer(Timer);
}

void ATPGameModeBase::ReS_UpdateClearMissionNum_Implementation()
{
	OnRep_ClearMission();

}