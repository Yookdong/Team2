// Fill out your copyright notice in the Description page of Project Settings.


#include "BG/BGPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BG/BGBaseCharacter.h"

ABGPlayerController::ABGPlayerController()
{
	bIsThirdView = true;
	bIsOpenInven = false;
	ControlledPawn = nullptr;
}

void ABGPlayerController::BeginPlay()
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

void ABGPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	UE_LOG(LogTemp, Display, TEXT("OnPossess"));

	if (aPawn != nullptr)
	{
		ControlledPawn = Cast<ABGBaseCharacter>(GetPawn());
	}
}

void ABGPlayerController::OpenInventory()
{
}