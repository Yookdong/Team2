// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TPPlayerController.h"
#include "InventorySystemComponent.h"
#include "Components/WrapBox.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Display, TEXT("inven widget construct"));

	ATPPlayerController* tpcontroller = Cast<ATPPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(tpcontroller != nullptr)
	{
		invencomponent = tpcontroller->GetComponentByClass<UInventorySystemComponent>();

		UpdateInven(); // 이게 생성자에 있어서 터지는 거 같음 pre construct 로 바꿔봐야 할 듯
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
