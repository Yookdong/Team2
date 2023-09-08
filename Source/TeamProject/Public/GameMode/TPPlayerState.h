// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_UpdateHP_TwoParams, float, CurrentHP, float, MaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateUserName, const FString&, UserName);

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ATPPlayerState : public APlayerState
{
	GENERATED_BODY()
private:

public:
	ATPPlayerState();

	void UpdateBind();

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHP)
	float CurrentHP;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHP)
	float MaxHP;

	UPROPERTY(ReplicatedUsing = OnRep_UserName)
	FString UserName;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateHP_TwoParams Fuc_Dele_UpdateHP;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateUserName Func_Dele_UpdateUserName;

	// Fuction
	UFUNCTION(BlueprintCallable)
	void AddDamage(float damage);

	UFUNCTION(BlueprintCallable)
	void Heal(float heal);

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
	void OnRep_UserName();

	// TimerHandle
	FTimerHandle TH_UpdateBind;
};
