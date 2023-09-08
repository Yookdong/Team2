// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "GameFramework/Character.h"
#include "ItemDataComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create
	ItemBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// Inherit
	SetRootComponent(ItemBaseMesh);

	// ETC Setting
	ItemBaseMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::EventGetItem_Implementation()
{
}

void AItemBase::EventDrop_Implementation()
{
}

void AItemBase::EventEquip_Implementation(ACharacter* target)
{
	OwnerChar = target;

	ItemBaseMesh->SetSimulatePhysics(false);

	// AttachToComponent(target->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weapon"));
}

void AItemBase::EventTrigger_Implementation()
{
}

void AItemBase::IsCanGetItem_Implementation(bool& outiscan)
{
	outiscan = !IsValid(OwnerChar);
}

void AItemBase::IsCanUseItem_Implementation(bool& outiscan)
{
	outiscan = IsValid(OwnerChar);
}