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
	class UTextBlock* TimerText;

public:
	UPlayHUDWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void OpenInven();
	void CloseInven();

	void UpdateHP(float current, float max);
	void UpdateOX(float current, float max);
	void UpdateTimer(float time);
};
