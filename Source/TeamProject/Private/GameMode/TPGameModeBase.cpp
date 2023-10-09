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


void ATPGameModeBase::AddClearMissionNum()
{
	ClearMissionNum++;

	OnRep_ClearMission();
}

void ATPGameModeBase::OnRep_Timer()
{
	if (Fuc_Dele_UpdateTimer.IsBound())
		Fuc_Dele_UpdateTimer.Broadcast(Timer);
}

void ATPGameModeBase::OnRep_ClearMission()
{
	if (Fuc_Dele_UpdateClearMissionNum.IsBound())
		Fuc_Dele_UpdateClearMissionNum.Broadcast(ClearMissionNum);
}

void ATPGameModeBase::UpdateTimer(float newtime)
{
	//int32 num = 0;

	////Find All PC
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		ATPPlayerController* PC = Cast<ATPPlayerController>(*Iter);
		if (PC)
		{
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
	Res_StartTimer();
}

void ATPGameModeBase::Req_PassedTime_Implementation(float time)
{
	Res_PassedTime(time);
}

void ATPGameModeBase::Req_UpdateClearMissionNum_Implementation()
{
	ReS_UpdateClearMissionNum();
}

// Server to Client
void ATPGameModeBase::Res_StartTimer_Implementation()
{
	bIsStart = !bIsStart;
}

void ATPGameModeBase::Res_PassedTime_Implementation(float time)
{
	Timer -= time;

	Timer = FMath::Clamp(Timer, 0, MaxTimer);

	OnRep_Timer();
	//UpdateTimer(Timer);
}

void ATPGameModeBase::ReS_UpdateClearMissionNum_Implementation()
{
	OnRep_ClearMission();
}