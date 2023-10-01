// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "TPBaseCharacter.h"
#include "InventoryComponent.h"
#include "TPGameHUD.h"
//#include "Net/UnrealNetwork.h"


ATPPlayerController::ATPPlayerController()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InvenComponent"));

	bIsThirdView = true;
	bIsOpenInven = false;
	ControlledPawn = nullptr;
}

void ATPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if (Subsystem && DefaultMappingContext)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATPPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (aPawn != nullptr)
	{
		ControlledPawn = Cast<ATPBaseCharacter>(GetPawn());
	}
}

bool ATPPlayerController::AddtoInven(FName name, int32 quantity)
{
	InventoryComponent->AddToInventory(name, quantity);
	return false;
}


// Client to Server
void ATPPlayerController::ReqTrigger_Implementation()
{
	ControlledPawn->GetEquipItem();
	ResTrigger();
}

void ATPPlayerController::ReqPressF_Implementation()
{
	if (InventoryComponent->GetLookatActor() != nullptr)
	{
		InventoryComponent->ReqInteract();
	}
}


// Server to Client
void ATPPlayerController::ResTrigger_Implementation()
{
}

void ATPPlayerController::ResPressF_Implementation()
{
}


// Input Function
void ATPPlayerController::SetupInactiveStateInputComponent(UInputComponent* InComponent)
{
	Super::SetupInactiveStateInputComponent(InComponent);

	// Set up action bindings
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InComponent);

	if (EnhancedInputComponent)
	{
		//Trigger
		EnhancedInputComponent->BindAction(TriggerAction, ETriggerEvent::Started, this, &ATPPlayerController::Trigger);

		//PressF
		EnhancedInputComponent->BindAction(PressFAction, ETriggerEvent::Started, this, &ATPPlayerController::PressF);

		//PressI
		EnhancedInputComponent->BindAction(PressIAction, ETriggerEvent::Started, this, &ATPPlayerController::PressI);
	}
}

void ATPPlayerController::Trigger(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Display, TEXT("Trigger"));
	ReqTrigger();
}

void ATPPlayerController::PressF(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Display, TEXT("PressF"));
	ReqPressF();
}

void ATPPlayerController::PressI(const FInputActionValue& value)
{
	ATPGameHUD* hud = Cast<ATPGameHUD>(GetHUD());
	if (hud == nullptr) return;

	if (bIsOpenInven)
	{
		bIsOpenInven = !bIsOpenInven;
		hud->OpenInven();
	}
	else
	{
		bIsOpenInven = !bIsOpenInven;
		hud->CloseInven();
	}
}