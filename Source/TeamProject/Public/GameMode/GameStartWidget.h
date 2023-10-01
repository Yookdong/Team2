// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDele_IsStart);
/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UGameStartWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	class UTextBlock* MissionDesriptBox;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void GameStart();

	UPROPERTY(ReplicatedUsing = OnRep_bIsStart)
	bool bIsStart;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_IsStart Fuc_Dele_IsStart;

	UFUNCTION()
	void OnRep_bIsStart();
};
