// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInterface.h"
#include "GameMode/TPDataTableManager.h"
#include "ItemDataComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMPROJECT_API UItemDataComponent : public UActorComponent, public IItemInterface
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Quantity;

public:	
	// Sets default values for this component's properties
	UItemDataComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

	// Interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemEvent)
	void InteractWith(ATPPlayerController* playercontroller);

	virtual void InteractWith_Implementation(ATPPlayerController* playercontroller) override;

		
};
