// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "GameMode/TPDataTableManager.h"
#include "ItemBase.generated.h"

UCLASS()
class TEAMPROJECT_API AItemBase : public AActor, public IItemInterface
{
	GENERATED_BODY()
private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemBaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UItemDataComponent* ItemDataComponent;

	// 일반 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ACharacter* OwnerChar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FST_Item ST_Item;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FST_Slot ST_Slot;

public:	
	// Sets default values for this actor's properties
	AItemBase();

	// Getter
	EITEMTYPE GetItemType() { return ST_Item.ItemMainType; }
	ESUBTYPE GetSubType() { return ST_Item.ItemSubType; }
	ACharacter* GetOwnerChar() { return OwnerChar; }
	UStaticMeshComponent* GetItemBaseMesh() { return ItemBaseMesh; }

	// Setter
	void SetItemType(EITEMTYPE type) { ST_Item.ItemMainType = type; }
	void SetSubType(ESUBTYPE type) { ST_Item.ItemSubType = type; }
	void SetOwnerChar(ACharacter* character) { OwnerChar = character; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	// Function

	// Client to Server

	// Server to Client

	// Interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void EventGetItem();

	virtual void EventGetItem_Implementation() override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void EventDrop();

	virtual void EventDrop_Implementation() override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void EventEquip(ACharacter* target);

	virtual void EventEquip_Implementation(ACharacter* target) override;


	/// <summary>
	/// Use the Item
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void EventTrigger();

	virtual void EventTrigger_Implementation() override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void IsCanGetItem(bool& iscan);

	virtual void IsCanGetItem_Implementation(bool& outiscan) override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void IsCanUseItem(bool& iscan);

	virtual void IsCanUseItem_Implementation(bool& outiscan) override;
};
