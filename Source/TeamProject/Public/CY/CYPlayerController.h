// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CYPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ACYPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	//========= Component =====================
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
		class AInventoryComponent* InventoryComponent;

	//========= variable =====================
	bool bIsThirdView;
	bool bIsOpenInven;
	class ACYBaseCharacter* ControlledPawn;


public:
	ACYPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;

public:
	void OpenInventory();

	// Getter
	bool bGetThirdView() { return bIsThirdView; }

	// Setter
	void bSetThirdView(bool value) { bIsThirdView = value; }



	//========= Input =====================
private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;


};
