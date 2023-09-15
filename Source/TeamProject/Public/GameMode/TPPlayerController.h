// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ATPPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	//========= Component =====================
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	//========= variable =====================
	bool bIsThirdView;
	bool bIsOpenInven;
	class ATPBaseCharacter* ControlledPawn;
	class UPlayHUDWidget* PlayHUDWidget;

public:
	ATPPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;

public:
	// Getter
	bool bGetThirdView() { return bIsThirdView; }

	// Setter
	void bSetThirdView(bool value) { bIsThirdView = value; }
	void SetPlayHUDWidget(UPlayHUDWidget* value) { PlayHUDWidget = value; }


	//========= Input =====================
	/** Sets up input bindings for the input component pushed on the stack in the inactive state. */
	virtual void SetupInactiveStateInputComponent(UInputComponent* InComponent) override;

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Trigger Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* TriggerAction;

	/** PressF Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PressFAction;

	/** PressI Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PressIAction;

protected:
	///** Sets up input bindings for the input component pushed on the stack in the inactive state. */
	//virtual void SetupInactiveStateInputComponent(UInputComponent* InComponent) override;

	/** Called for Shooting input */
	void Trigger(const FInputActionValue& value);

	/** Called for PressF input */
	void PressF(const FInputActionValue& value);

	/** Called for PressI input */
	void PressI(const FInputActionValue& value);
};
