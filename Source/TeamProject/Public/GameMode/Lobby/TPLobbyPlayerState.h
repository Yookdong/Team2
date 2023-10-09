// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPLobbyPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Lobby_UserName, const FString&, UserName);
/**
 *
 */
UCLASS()
class TEAMPROJECT_API ATPLobbyPlayerState : public APlayerState
{
	GENERATED_BODY()
private:
	FTimerHandle TH_UpdateBind;

public:
	ATPLobbyPlayerState();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(ReplicatedUsing = OnRep_UserName)
	FString UserName;

	UFUNCTION(BlueprintCallable)
	FString GetUserName() { return UserName; }

	UFUNCTION(BlueprintCallable)
	void SetUserName(const FString& name);

	UFUNCTION()
	void OnRep_UserName();

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_Lobby_UserName Func_Dele_UpdateUserName;

	void UpdateBind();

};

