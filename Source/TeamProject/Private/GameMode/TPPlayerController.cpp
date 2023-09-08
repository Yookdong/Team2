// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "TPBaseCharacter.h"
#include "PlayHUDWidget.h"

ATPPlayerController::ATPPlayerController()
{
	bIsThirdView = true;
	bIsOpenInven = false;
	ControlledPawn = nullptr;
}

void ATPPlayerController::BeginPlay()
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

void ATPPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	UE_LOG(LogTemp, Display, TEXT("OnPossess"));

	if (aPawn != nullptr)
	{
		ControlledPawn = Cast<ATPBaseCharacter>(GetPawn());
	}
}


// Input Function
void ATPPlayerController::SetupInactiveStateInputComponent(UInputComponent* InComponent)
{
	Super::SetupInactiveStateInputComponent(InComponent);

	UE_LOG(LogTemp, Display, TEXT("Controller Input Binding"));

	// Set up action bindings
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InComponent);

	if (EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Display, TEXT("cast success"));

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
}

void ATPPlayerController::PressF(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Display, TEXT("PressF"));
}

void ATPPlayerController::PressI(const FInputActionValue& value)
{
	if (bIsOpenInven)
	{
		PlayHUDWidget->CloseInven();
		bIsOpenInven = !bIsOpenInven;
	}
	else
	{
		PlayHUDWidget->OpenInven();
		bIsOpenInven = !bIsOpenInven;
	}
}