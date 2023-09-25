// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/OXZone.h"
#include "Components/BoxComponent.h"
#include "TPBaseCharacter.h"

// Sets default values
AOXZone::AOXZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	SetRootComponent(BoxCollision);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AOXZone::OnCollisionBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AOXZone::OnCollisionEndOverlap);

	InCharacter = nullptr;

	HaveOX = 30.0f;
}

// Called when the game starts or when spawned
void AOXZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOXZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOXZone::AddOX()
{
	InCharacter->ChargeOX(HaveOX);
}

void AOXZone::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InCharacter = Cast<ATPBaseCharacter>(OtherActor);
	
	if (IsValid(InCharacter))
	{
		AddOX();
		GetWorldTimerManager().SetTimer(TH_OXZone, this, &AOXZone::AddOX, 3.0f, true);
	}
}

void AOXZone::OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATPBaseCharacter* character = Cast<ATPBaseCharacter>(OtherActor);

	if (IsValid(character))
	{
		GetWorldTimerManager().ClearTimer(TH_OXZone);
		InCharacter = nullptr;
	}
}

