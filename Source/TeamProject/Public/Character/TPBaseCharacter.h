// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameMode/TPDataTableManager.h"
#include "TPBaseCharacter.generated.h"

UCLASS()
class TEAMPROJECT_API ATPBaseCharacter : public ACharacter
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
	class USceneCaptureComponent2D* MiniMapCapture;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MiniMap, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* IconforMiniMap;


	//-------- variable --------
	FST_Character* CharacterData;

	// Notify 변수
	UPROPERTY(ReplicatedUsing = OnRep_EquipItem)
	AActor* EquipItem;

	// Timer Handle
	FTimerHandle TH_BindPlayerState;
	FTimerHandle TH_OXZero;

public:
	// Sets default values for this character's properties
	ATPBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BindPlayerState();
	void Die();
	void ChargeOX(float charge);
	void AddDamage();

	// Getter
	AActor* GetEquipItem() { return EquipItem; }

	UFUNCTION(BlueprintPure)
	bool IsEquip() { return IsValid(EquipItem); }


	// Setter
	void SetThirdView();
	void SetFirstView();
	void SetCharacter();


	// 연결
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EventUpdateHP(float curhp, float maxhp);

	virtual void EventUpdateHP_Implementation(float curhp, float maxhp);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EventUpdateOX(float curox, float maxox);

	virtual void EventUpdateOX_Implementation(float curox, float maxox);


	// Client to Server


	// Server to Client
	UFUNCTION()
	void OnRep_EquipItem();



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

	/** Called for ViewChange input */
	void ViewChange(const FInputActionValue& value);

};
