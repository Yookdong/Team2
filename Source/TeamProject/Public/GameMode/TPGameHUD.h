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

public:
	virtual void BeginPlay() override;

	void BindPlayerState(class ATPPlayerState* tpstate);

	void OpenInven();
	void CloseInven();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyHP(float curhp, float maxhp);

	void OnUpdateMyHP_Implementation(float curhp, float maxhp);


	// TimerHandle
	FTimerHandle th_BindMyPlayerState;
};
