// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPDataTableManager.h"
#include "Item/ItemInterface.h"
#include "InventoryComponent.generated.h"

DECLARE_DELEGATE(FDele_UpdateInven);

UCLASS()
class TEAMPROJECT_API UInventoryComponent : public UActorComponent, public IItemInterface
{
	GENERATED_BODY()
private:
	// 일반 변수 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Slot, meta = (AllowPrivateAccess = "true"))
	TArray<FST_Slot> Contents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot, meta = (AllowPrivateAccess = "true"))
	int32 InvenSize;

	// 아이템 정보창
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> ItemInfoWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UItemInfoWidget* ItemInfoWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InteractionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InteractionRadius;

	class AActor* LookatActor;

public:	
	// Sets default values for this actor's properties
	UInventoryComponent();

	// Event Dispatcher
	FDele_UpdateInven FUpdateInvenDele;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getter
	TArray<FST_Slot> GetContentArray() { return Contents; }
	AActor* GetLookatActor() { return LookatActor; }

	// Setter
	void SetContentsArray(const TArray<FST_Slot>& newArray);


	// Function
	void IntertactionItem();
	void IsLookingItem();
	void TransferSlot(int sourceIndex, UInventoryComponent* invenComp, int destination);
	bool AddToInventory(FName itemid, int32 quantity);
	int FindSlot(FName name, bool& outresult);
	void AddToStack(int index, int32 quantity);

	// Client to Server
	UFUNCTION(Server, Reliable)
	void ReqInteract();

	UFUNCTION(Server, Reliable)
	void ReqTransferSlot(int index, UInventoryComponent* inven, int destination);

	UFUNCTION(Server, Reliable, WithValidation)
	void ReqSetContentsArray(const TArray<FST_Slot>& newArray);
	// Replicated TArray의 Setter 함수의 유효성 검사 함수
	bool ReqSetContentsArray_Validate(const TArray<FST_Slot>& newArray);
	// Replicated TArray의 Setter 함수의 구현 함수
	void ReqSetContentsArray_Implementation(const TArray<FST_Slot>& newArray);


	// Server to Client
	UFUNCTION(NetMulticast, Reliable)
	void InvenUpdate();

	UFUNCTION(Client, Reliable)
	void OnLocalInteract(AActor* target, ATPPlayerController* interActor);	
};
