// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UPlayHUDWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<class UInventoryWidget> InvenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<class UPlayerInfoWidget> PlayerInfoWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	class UGameStartWidget* GameStartWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<class UGameClearWidget> GameClearWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<class UGameOverWidget> GameOverWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<class UPauseWidget> MenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	class UTextBlock* TimerText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ClearMissionNum;
	
public:
	virtual void NativeConstruct() override;

	// Getter
	class UGameStartWidget* GetStartWidget() { return GameStartWidget; }

	// Widget On//Off
	void OpenInven();
	void CloseInven();
	void OpenGameClear();
	void OpenGameOver();
	void OpenMenu();

	// About Bind
	void UpdateHP(float current, float max);
	void UpdateOX(float current, float max);
	void UpdateClearMissionNum(float clearnum);

	// Client to Server
	UFUNCTION(Server, Reliable)
	void Req_UpdateTimer(float time);

	// Server to Client
	UFUNCTION(NetMulticast, Reliable)
	void Res_UpdateTimer(float time);
};
