// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "TPDataTableManager.h"
#include "TPGameInstance.generated.h"

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
	void SetUserName(FString name) { UserName = name; }

	// SelectCharType
	ECHARTYPE GetSelectCharType() { return SelectCharType; }

	UFUNCTION(BlueprintCallable)
	void SetSelectCharType(ECHARTYPE type) { SelectCharType = type; }
	
	FName SetCharacterRowName();

};
