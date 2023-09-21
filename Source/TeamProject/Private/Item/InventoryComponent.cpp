// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/InventoryComponent.h"
#include "Item/ItemInfoWidget.h"
#include "Item/ItemDataComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TPPlayerController.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Net/UnrealNetwork.h"


// Sets default values
UInventoryComponent::UInventoryComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	InvenSize = 6;
	InteractionRange = 300.0f;
	InteractionRadius = 15.0;
	LookatActor = nullptr;
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, Contents);
}

// Called when the game starts or when spawned
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Contents.SetNum(InvenSize);

	ItemInfoWidget = CreateWidget<UItemInfoWidget>(GetWorld(), ItemInfoWidgetClass);
	ItemInfoWidget->AddToViewport();
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FUpdateInvenDele.Unbind();
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	IntertactionItem();
}

void UInventoryComponent::SetContentsArray(const TArray<FST_Slot>& newArray)
{
	Contents = newArray;
	// 서버에 변경된 배열을 알림
	if (GetOwner()->HasAuthority())
	{
		Contents = newArray;
	}
	else
	{
		// 클라이언트에서 서버로 변경된 배열을 보냄
		ReqSetContentsArray(newArray);
	}
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
		if (hitinfo.GetActor() != LookatActor)
		{
			LookatActor = hitinfo.GetActor();

			IItemInterface* itemIF = Cast< IItemInterface>(LookatActor);
			if (itemIF!=nullptr)
			{
				ItemInfoWidget->ShowMessage(itemIF->Execute_LookAt(LookatActor));
			}
		}
	}
	else
	{
		LookatActor = nullptr;
		ItemInfoWidget->ShowMessage(FText());
	}
}

void UInventoryComponent::IsLookingItem()
{
	if (IsValid(LookatActor))
	{
		UItemDataComponent* invenDataComp = LookatActor->GetComponentByClass<UItemDataComponent>();
		if (invenDataComp != nullptr)
		{
			ATPPlayerController* pc = Cast< ATPPlayerController>(GetOwner());
			if (pc)
			{
				IItemInterface* itemIF = Cast< IItemInterface>(invenDataComp);
				if (itemIF)
				{
					itemIF->Execute_InteractWith(invenDataComp, pc);
				}
			}
		}
		else
		{
			ATPPlayerController* pc = Cast< ATPPlayerController>(GetOwner());
			if (pc)
			{
				LookatActor->SetOwner(pc);
				OnLocalInteract(LookatActor, pc);
			}
		}
	}
}

void UInventoryComponent::TransferSlot(int sourceIndex, UInventoryComponent* invenComp, int destination)
{
	FST_Slot localContent;
	localContent = invenComp->GetContentArray()[sourceIndex];

	if (destination < 0) return;

	if (localContent.ItemID == invenComp->GetContentArray()[destination].ItemID)
	{
		invenComp->GetContentArray().SetNum(sourceIndex);
	}
	else
	{

	}
}

bool UInventoryComponent::AddToInventory(FName itemid, int32 quantity)
{
	int32 value = quantity;
	bool faild = false;
	
	while (value > 0 && !faild)
	{
		bool result;

		int index = FindSlot(itemid, result);

		if (result)
		{
			AddToStack(index, 1);
			value--;
		}
		else
		{

		}
	}

	return !faild;
}

int UInventoryComponent::FindSlot(FName name, bool& outresult)
{
	return 0;
}

void UInventoryComponent::AddToStack(int index, int32 quantity)
{
}


// Client to Server
void UInventoryComponent::ReqInteract_Implementation()
{
	IsLookingItem();
}

void UInventoryComponent::ReqTransferSlot_Implementation(int index, UInventoryComponent* inven, int destination)
{
	TransferSlot(index, inven, destination);
}

bool UInventoryComponent::ReqSetContentsArray_Validate(const TArray<FST_Slot>& newArray)
{
	return false;
}

void UInventoryComponent::ReqSetContentsArray_Implementation(const TArray<FST_Slot>& newArray)
{
	SetContentsArray(newArray);
}


// Server to Client
void UInventoryComponent::InvenUpdate_Implementation()
{
	if (FUpdateInvenDele.IsBound())
	{
		FUpdateInvenDele.Execute();
	}
}

void UInventoryComponent::OnLocalInteract_Implementation(AActor* target, ATPPlayerController* interActor)
{
	IItemInterface* itemIF = Cast< IItemInterface>(target);
	if (itemIF)
	{
		itemIF->Execute_InteractWith(target, interActor);
	}
}
