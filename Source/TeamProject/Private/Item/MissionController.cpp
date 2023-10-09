// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/MissionController.h"
#include "TPGameModeBase.h"

// Sets default values
AMissionController::AMissionController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsClear = false;
}

// Called when the game starts or when spawned
void AMissionController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsClear)
	{
		ReqAddScore();
	}
}

void AMissionController::ReqAddScore_Implementation()
{
	// 게임 모드에 있는 변수 올리는 코드 짜면 됨
	ATPGameModeBase* GameMode = Cast<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
	UE_LOG(LogTemp, Warning, TEXT("ReqAddScore Call"));

	if (GameMode)
	{
		GameMode->AddClearMissionNum();
		UE_LOG(LogTemp, Warning, TEXT("ClearMissionNum: %d"), GameMode->ClearMissionNum);
		ResAddScore();
	}	
}

void AMissionController::ResAddScore_Implementation()
{
	bIsClear = false;
}
