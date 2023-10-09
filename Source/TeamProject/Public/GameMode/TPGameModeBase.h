// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateTimer, float, Timer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateClearMissionNum, float, ClearMissionNum);
/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ATPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxMission;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurrentCharNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxTimer;

	bool bIsStart;
	bool bIsBindClear;

public:
	ATPGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Timer)
	float Timer;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateTimer Fuc_Dele_UpdateTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ClearMission)
	int ClearMissionNum;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateClearMissionNum Fuc_Dele_UpdateClearMissionNum;

	FTimerHandle TH_UpdateTimer;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	void BindFunction();

	UFUNCTION(BlueprintCallable)
	void AddCharNum() { CurrentCharNum++; }

	UFUNCTION(BlueprintCallable)
	void AddClearMissionNum();

	// Network
	UFUNCTION()
	void OnRep_Timer();

	UFUNCTION()
	void OnRep_ClearMission();

	UFUNCTION(BlueprintCallable)
	void UpdateTimer(float newtime);

	// Client to Server
	UFUNCTION(Server, Reliable)
	void Req_StartTimer();

	UFUNCTION(Server, Reliable)
	void Req_PassedTime(float time);

	UFUNCTION(Server, Reliable)
	void Req_UpdateClearMissionNum();

	// Server to Client
	UFUNCTION(NetMulticast, Reliable)
	void Res_StartTimer();

	UFUNCTION(NetMulticast, Reliable)
	void Res_PassedTime(float time);

	UFUNCTION(NetMulticast, Reliable)
	void ReS_UpdateClearMissionNum();
};
