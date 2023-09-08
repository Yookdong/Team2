// Fill out your copyright notice in the Description page of Project Settings.


#include "CY/CYPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CY/CYBaseCharacter.h"

ACYPlayerController::ACYPlayerController()
{
	bIsThirdView = true;
	bIsOpenInven = false;
	ControlledPawn = nullptr;
}

void ACYPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("controll BeginPlay"));

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if (Subsystem && DefaultMappingContext)
	{
		UE_LOG(LogTemp, Display, TEXT("BeginPlay Input Binding"));

		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ACYPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	UE_LOG(LogTemp, Display, TEXT("OnPossess"));

	if (aPawn != nullptr)
	{
		ControlledPawn = Cast<ACYBaseCharacter>(GetPawn());
	}
}

void ACYPlayerController::OpenInventory()
{
}