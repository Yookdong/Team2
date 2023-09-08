// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameMode/TPDataTableManager.h"
#include "JHBaseCharacter.generated.h"

UCLASS()
class TEAMPROJECT_API AJHBaseCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	//------- Component -------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FolloCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* FirstMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MiniMap, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* MapCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MiniMap, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* MiniMapCamera;


	//-------- variable --------
	FST_Character* CharacterData;


public:
	// Sets default values for this character's properties
	AJHBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetThirdView();
	void SetFirstView();
	void SetCharacter();


//======== Input ============
private:
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Trigger Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TriggerAction;

	/** PressF Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PressFAction;

	/** PressI Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PressIAction;

	/** PressI Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ViewChangeAction;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for movement input */
	void Move(const FInputActionValue& value);

	/** Called for looking input */
	void Look(const FInputActionValue& value);

	/** Called for Shooting input */
	void Trigger(const FInputActionValue& value);

	/** Called for PressF input */
	void PressF(const FInputActionValue& value);

	/** Called for PressI input */
	void PressI(const FInputActionValue& value);

	/** Called for ViewChange input */
	void ViewChange(const FInputActionValue& value);

};
