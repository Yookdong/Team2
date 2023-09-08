// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TPPlayerController.h"
#include "InventorySystemComponent.h"
#include "Components/WrapBox.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ATPPlayerController* jhcontroller = Cast<ATPPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (jhcontroller != nullptr)
	{
		invencomponent = jhcontroller->GetComponentByClass<UInventorySystemComponent>();

		UpdateInven();
	}
}

void UInventoryWidget::UpdateInven()
{
	InvenGrid->ClearChildren();

	if (invencomponent != nullptr)
	{
	}
}

void UInventoryWidget::OpenInven()
{
	// 생성 되어 있는디
}

void UInventoryWidget::CloseInven()
{
	// 이것도 생성인되어 있는디
}
