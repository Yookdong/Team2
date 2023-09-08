// Fill out your copyright notice in the Description page of Project Settings.


#include "JH/JHPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "JH/JHBaseCharacter.h"
#include "InventorySystemComponent.h"
#include "TPGameHUD.h"

AJHPlayerController::AJHPlayerController()
{
	// create
	InventoryComponent = CreateDefaultSubobject<UInventorySystemComponent>(TEXT("Inventory"));

	// ETC Setting
	bIsThirdView = true;
	bIsOpenInven = false;
	ControlledPawn = nullptr;
}

void AJHPlayerController::BeginPlay()
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

void AJHPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	UE_LOG(LogTemp, Display, TEXT("OnPossess"));

	if (aPawn != nullptr)
	{
		ControlledPawn = Cast<AJHBaseCharacter>(GetPawn());
	}
}

void AJHPlayerController::OpenInventory()
{
	AHUD* hud = Cast<ATPGameHUD>(GetHUD());

	if (hud != nullptr)
	{

	}
}