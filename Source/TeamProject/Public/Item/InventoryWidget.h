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

	class UInventoryComponent* invencomponent;

public:
	virtual void NativePreConstruct() override;

	void OpenInven();
	void CloseInven();

	UFUNCTION()
	void OnUpdateInven();
};
