// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/InventoryComponent.h"

// Sets default values
AInventoryComponent::AInventoryComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InvenSize = 6;
}

// Called when the game starts or when spawned
void AInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Content.SetNum(InvenSize);
}

// Called every frame
void AInventoryComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

