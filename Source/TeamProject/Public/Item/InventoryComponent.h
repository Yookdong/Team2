// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPDataTableManager.h"
#include "InventoryComponent.generated.h"

UCLASS()
class TEAMPROJECT_API AInventoryComponent : public AActor
{
	GENERATED_BODY()
private:
	// 일반 변수 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot, meta = (AllowPrivateAccess = "true"))
	TArray<FST_Slot> Content;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot, meta = (AllowPrivateAccess = "true"))
	int InvenSize;

public:	
	// Sets default values for this actor's properties
	AInventoryComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
