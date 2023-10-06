// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALobbyPlayerController();

	virtual void OnPossess(APawn* aPawn) override;

	// Client to Server
	UFUNCTION(Client, Reliable)
	void ResClientPossess();

	// Server to Client
	UFUNCTION(Server, Reliable)
	void ReqChangeUserName(const FString& name);
};
