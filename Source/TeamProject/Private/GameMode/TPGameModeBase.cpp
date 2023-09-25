// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPGameModeBase.h"
#include "Net/UnrealNetwork.h"

ATPGameModeBase::ATPGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ClearMission = 0;
	MaxMission = 0;
	CurrentCharNum = 0;
	Timer = 1200.0f;
}

void ATPGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPGameModeBase, Timer);
}

void ATPGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATPGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PassedTime(DeltaSeconds);

	if (ClearMission >= MaxMission)
	{
		// GameClear
	}
}

void ATPGameModeBase::PassedTime(float time)
{
	Timer -= time;

	OnRep_Timer();
}

void ATPGameModeBase::OnRep_Timer()
{
	if (Fuc_Dele_UpdateTimer.IsBound())
		Fuc_Dele_UpdateTimer.Broadcast(Timer);
}
