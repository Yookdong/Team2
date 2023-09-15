// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemInfoWidget.h"
#include "Components/TextBlock.h"

UItemInfoWidget::UItemInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MessageBox = nullptr;
	Message = FText();
}

void UItemInfoWidget::NativePreConstruct()
{
	if (Message.IsEmpty())
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		this->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UItemInfoWidget::ShowMessage(const FText& text)
{
	if (MessageBox != nullptr)
	{
		Message = text;
		MessageBox->SetText(Message);

		if (Message.IsEmpty())
		{
			this->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			this->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
}
