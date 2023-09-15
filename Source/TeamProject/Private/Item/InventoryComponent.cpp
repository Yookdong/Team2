// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/InventoryComponent.h"
#include "Item/ItemInfoWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
UInventoryComponent::UInventoryComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	InvenSize = 6;
	InteractionRange = 300.0f;
	InteractionRadius = 15.0;
	LookAtActor = nullptr;
}

// Called when the game starts or when spawned
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Content.SetNum(InvenSize);

	ItemInfoWidget = CreateWidget<UItemInfoWidget>(GetWorld(), ItemInfoWidgetClass);
	ItemInfoWidget->AddToViewport();

}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	IntertactionItem();
}

void UInventoryComponent::IntertactionItem()
{
	FHitResult hitinfo;

	FVector startVector;
	FVector endVector;

	TArray<TEnumAsByte<EObjectTypeQuery>> objectType;
	objectType.Add(EObjectTypeQuery::ObjectTypeQuery7);

	TArray<AActor*> notTarget;
	notTarget.Add(GetOwner());

	APlayerCameraManager* pcm = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if(pcm)
	{
		startVector = pcm->GetCameraLocation();
		endVector = (pcm->GetActorForwardVector() * InteractionRange) + startVector;
	}

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), startVector, endVector, InteractionRadius, objectType, false, notTarget, EDrawDebugTrace::None, hitinfo, true, FLinearColor::Red, FLinearColor::Green);

	if (bHit)
	{
		if (hitinfo.GetActor() != LookAtActor)
		{
			LookAtActor = hitinfo.GetActor();

			IItemInterface* itemIF = Cast< IItemInterface>(LookAtActor);
			if (itemIF!=nullptr)
			{
				ItemInfoWidget->ShowMessage(itemIF->Execute_LookAt(LookAtActor));
			}
		}
	}
	else
	{
		LookAtActor = nullptr;
		ItemInfoWidget->ShowMessage(FText());
	}
}

