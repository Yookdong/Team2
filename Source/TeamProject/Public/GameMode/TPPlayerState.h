// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_UpdateHP, float, CurrentHP, float, MaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_UpdateOX, float, CurrentOX, float, MaxOX);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateUserName, const FString&, UserName);

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ATPPlayerState : public APlayerState
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	bool bIsStart;
	
public:
	ATPPlayerState();

protected:
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentHP)
	float CurrentHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHP)
	float MaxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentOX)
	float CurrentOX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxOX)
	float MaxOX;

	UPROPERTY(ReplicatedUsing = OnRep_UserName)
	FString UserName;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateHP Fuc_Dele_UpdateHP;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateOX Fuc_Dele_UpdateOX;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateUserName Func_Dele_UpdateUserName;

	// Fuction
	UFUNCTION(BlueprintCallable)
	void AddDamage(float damage);

	UFUNCTION(BlueprintCallable)
	void Heal(float heal);

	UFUNCTION(BlueprintCallable)
	void UseOX(float ox);

	UFUNCTION(BlueprintCallable)
	void ChargeOX(float ox);

	UFUNCTION(BlueprintCallable)
	FString GetUserName() { return UserName; }

	UFUNCTION(BlueprintCallable)
	void SetUserName(const FString& name);


	// NetWork
	UFUNCTION()
	void OnRep_CurrentHP();

	UFUNCTION()
	void OnRep_MaxHP();

	UFUNCTION()
	void OnRep_CurrentOX();

	UFUNCTION()
	void OnRep_MaxOX();

	UFUNCTION()
	void OnRep_UserName();

	// Server to Client
	UFUNCTION(Server, Reliable)
	void Req_SetIsStart();

	// Client to Server
	UFUNCTION(NetMulticast, Reliable)
	void Res_SetIsStart();

	// TimerHandle
	FTimerHandle TH_UpdateBind;
};
