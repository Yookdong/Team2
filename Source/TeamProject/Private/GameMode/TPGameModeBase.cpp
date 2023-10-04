// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPGameModeBase.h"
#include "Net/UnrealNetwork.h"

ATPGameModeBase::ATPGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ClearMissionNum = 0;
	MaxMission = 5;
	CurrentCharNum = 0;
	Timer = 1200.0f;
	bIsStart = false;

	UE_LOG(LogTemp, Display, TEXT("GameMode Constructor"));
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

	Timer = 1200.0f;
}

void ATPGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsStart)
	{
		Req_PassedTime(DeltaSeconds);
	}
}

void ATPGameModeBase::BindFunction(UGameStartWidget* widget)
{
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

	OnRep_Timer();
}

void ATPGameModeBase::ReS_UpdateClearMissionNum_Implementation()
{
	OnRep_ClearMission();
}