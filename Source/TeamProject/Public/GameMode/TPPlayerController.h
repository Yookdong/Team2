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

public:
	ATPPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;

public:
	bool AddtoInven(FName name, int32 quantity);

	// Getter
	bool bGetThirdView() { return bIsThirdView; }

	// Setter
	void bSetThirdView(bool value) { bIsThirdView = value; }

	// Client to Server
	UFUNCTION(Server, Reliable)
	void ReqTrigger();

	UFUNCTION(Server, Reliable)
	void ReqPressF();

	// Server to Client
	UFUNCTION(NetMulticast, Reliable)
	void ResTrigger();

	UFUNCTION(NetMulticast, Reliable)
	void ResPressF();


public:
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
	/** Called for Shooting input */
	void Trigger(const FInputActionValue& value);

	/** Called for PressF input */
	void PressF(const FInputActionValue& value);

	/** Called for PressI input */
	void PressI(const FInputActionValue& value);
};
