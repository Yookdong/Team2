// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"


UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class TEAMPROJECT_API IItemInterface
{
	GENERATED_BODY()
private:

public:
	/// <summary>
	/// into Inven
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void EventGetItem();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void EventDrop();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void EventEquip(ACharacter* target);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void InteractWith(APlayerController* pc);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	FText LookAt();

	/// <summary>
	/// Use the Item
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void EventTrigger();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void IsCanGetItem(bool& iscan);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void IsCanUseItem(bool& iscan);

};
