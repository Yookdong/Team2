// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMode/TPDataTableManager.h"
#include "TPCharSelectUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UTPCharSelectUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECHARTYPE SelectType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UTextBlock* CharTypeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<class UTextBlock> CharTypeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString CharType;

public:
	UTPCharSelectUserWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateType();

};
