 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<class UWrapBox> InvenGrid;

	class UInventorySystemComponent* invencomponent;

public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

	void UpdateInven();
	void OpenInven();
	void CloseInven();
};
