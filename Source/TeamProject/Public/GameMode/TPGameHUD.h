// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TPGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ATPGameHUD : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PlayHUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UPlayHUDWidget* PlayHUDWidget;

	FTimerHandle TH_BindPlayerState;

public:
	ATPGameHUD();

	virtual void BeginPlay() override;

	void BindFunction();

	void OpenInven();
	void CloseInven();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyHP(float curhp, float maxhp);

	void OnUpdateMyHP_Implementation(float curhp, float maxhp);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyOX(float curox, float maxox);

	void OnUpdateMyOX_Implementation(float curox, float maxox);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateGameTime(float timer);

	void OnUpdateGameTime_Implementation(float timer);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartGame();

	void StartGame_Implementation();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartTimer();

	void StartTimer_Implementation();

	// TimerHandle
	FTimerHandle th_BindMyPlayerState;

	void UpdateTimerBlock(float timer);

	void UpdateMissionNumBlock(float value);
};
