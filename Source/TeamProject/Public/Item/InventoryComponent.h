// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPDataTableManager.h"
#include "Item/ItemInterface.h"
#include "InventoryComponent.generated.h"

UCLASS()
class TEAMPROJECT_API UInventoryComponent : public UActorComponent, public IItemInterface
{
	GENERATED_BODY()
private:
	// 일반 변수 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot, meta = (AllowPrivateAccess = "true"))
	TArray<FST_Slot> Content;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot, meta = (AllowPrivateAccess = "true"))
	int InvenSize;

	// 아이템 정보창
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> ItemInfoWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UItemInfoWidget* ItemInfoWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InteractionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InteractionRadius;

	AActor* LookAtActor;

public:	
	// Sets default values for this actor's properties
	UInventoryComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getter
	TArray<FST_Slot> GetContent() { return Content; }

	// Setter

	// Function
	void IntertactionItem();
};
