// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	class UTextBlock* MessageBox;

	FText Message;

public:
	UItemInfoWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativePreConstruct() override;

	void ShowMessage(const FText& text);
};
