// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EntryHUD.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API AEntryHUD : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> EntryHudWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUserWidget* EntryHudWidget;

public:
	virtual void BeginPlay() override;
};
