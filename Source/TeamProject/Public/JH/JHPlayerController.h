// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "JHPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API AJHPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	//========= Component =====================
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UInventorySystemComponent* InventoryComponent;

	//========= variable =====================
	bool bIsThirdView;
	bool bIsOpenInven;
	class AJHBaseCharacter* ControlledPawn;


public:
	AJHPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;

public:
	void OpenInventory();

	// Getter
	bool IsOpenInven() { return bIsOpenInven; }
	bool bGetThirdView() { return bIsThirdView; }
	class UInventorySystemComponent* GetInvenComponent() { return InventoryComponent; }

	// Setter
	void SetOpenInven(bool value) { bIsOpenInven = value; }
	void bSetThirdView(bool value) { bIsThirdView = value; }



	//========= Input =====================
private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;


};
