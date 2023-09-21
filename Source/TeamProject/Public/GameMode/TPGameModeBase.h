// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateTimer, float, Timer);
/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ATPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ClearMission;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxMission;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurrentCharNum;

public:
	ATPGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Timer, meta = (AllowPrivateAccess = "true"))
	float Timer;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateTimer Fuc_Dele_UpdateTimer;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable)
	void AddCharNum() { CurrentCharNum++; }

	// Function
	void PassedTime(float time);

	// Network
	UFUNCTION()
	void OnRep_Timer();
};
