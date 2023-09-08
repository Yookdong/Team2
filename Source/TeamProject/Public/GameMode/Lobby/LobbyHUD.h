// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LobbyHUD.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> LobbyHudWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUserWidget* LobbyHudWidget;

public:
	virtual void BeginPlay() override;
};
