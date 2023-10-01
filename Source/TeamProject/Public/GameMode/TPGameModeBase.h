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

	bool bIsStart;

public:
	ATPGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Timer, meta = (AllowPrivateAccess = "true"))
	float Timer;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateTimer Fuc_Dele_UpdateTimer;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void BindFunction(class UGameStartWidget* widget);

public:
	UFUNCTION(BlueprintCallable)
	void AddCharNum() { CurrentCharNum++; }

	// Network
	UFUNCTION()
	void OnRep_Timer();

	// Client to Server
	UFUNCTION(Server, Reliable)
	void Req_StartTimer();

	UFUNCTION(Server, Reliable)
	void Req_PassedTime(float time);


	// Server to Client
	UFUNCTION(NetMulticast, Reliable)
	void Res_StartTimer();

	UFUNCTION(NetMulticast, Reliable)
	void Res_PassedTime(float time);
};
