// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HealItem.h"
#include "Components/SphereComponent.h"
#include "TPBaseCharacter.h"

// Sets default values
AHealItem::AHealItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BoxCollision"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(SphereCollision);
	Mesh->SetupAttachment(SphereCollision);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealItem::OnCollisionBeginOverlap);

	InCharacter = nullptr;

	HaveHP = 30.0f;
}

// Called when the game starts or when spawned
void AHealItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealItem::AddHP()
{
	InCharacter->Heal(HaveHP);
}

void AHealItem::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InCharacter = Cast<ATPBaseCharacter>(OtherActor);

	if (IsValid(InCharacter))
	{
		AddHP();
	}
}
