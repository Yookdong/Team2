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

public:
	void OpenInven();
	void CloseInven();
};
