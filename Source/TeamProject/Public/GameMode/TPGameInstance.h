// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TeamProject.h"
#include "FindSessionsCallbackProxy.h"
#include "Engine/DataTable.h"
#include "TPDataTableManager.h"
#include "Engine/GameInstance.h"
#include "TPGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_SessionResult, bool, IsFind, const TArray<FBlueprintSessionResult>&, SessionResult);

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UTPGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* CharacterData;

	FString UserName;

	ECHARTYPE SelectCharType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsGameClear;

public:
	UTPGameInstance();

protected:

public:
	// Data Table
	FST_Item* GetItemRowData(FName name);
	FST_Character* GetCharacterRowData();

	// UserName
	UFUNCTION(BlueprintPure)
	FString GetUserName() { return UserName; }

	UFUNCTION(BlueprintCallable)
	bool SetUserName(FString name);

	// SelectCharType
	ECHARTYPE GetSelectCharType() { return SelectCharType; }

	UFUNCTION(BlueprintCallable)
	void SetSelectCharType(ECHARTYPE type) { SelectCharType = type; }
	
	FName SetCharacterRowName();

	// Client to Server
	UFUNCTION(Server, Reliable)
	void ReqSetIsClear();

	// Server to Client
	UFUNCTION(NetMulticast, Reliable)
	void ResSetIsClear();

};
