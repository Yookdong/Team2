// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TPPlayerController.h"
#include "InventoryComponent.h"
#include "Components/WrapBox.h"


void UInventoryWidget::NativePreConstruct()
{
	UE_LOG(LogTemp, Display, TEXT("inven widget construct"));

	ATPPlayerController* tpcontroller = Cast<ATPPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (tpcontroller != nullptr)
	{
		invencomponent = tpcontroller->GetComponentByClass<UInventoryComponent>();

		OnUpdateInven(); // �̰� �����ڿ� �־ ������ �� ���� pre construct �� �ٲ���� �� ��

		if (invencomponent != nullptr)
		{
			invencomponent->FUpdateInvenDele.BindUFunction(this, FName("OnUpdateInven"));
		}
	}
}

void UInventoryWidget::OpenInven()
{
	// ���� �Ǿ� �ִµ�
}

void UInventoryWidget::CloseInven()
{
	// �̰͵� �����εǾ� �ִµ�
}


// Server to Client
void UInventoryWidget::OnUpdateInven()
{
	InvenGrid->ClearChildren();

	if (invencomponent != nullptr)
	{
	}
}