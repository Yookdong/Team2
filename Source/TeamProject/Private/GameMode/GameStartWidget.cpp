// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameStartWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UGameStartWidget::NativeConstruct()
{
	StartButton->OnClicked.AddDynamic(this, &UGameStartWidget::GameStart);

	// �̼� ���� ���� ���� �ҷ����� �ڵ尡 �ʿ���.
	// ���� ��Ʈ�� ��𼱰� �ҷ����ų� �ƿ� �׳� �۾� �ְų� �ؾ� �� ��
}

void UGameStartWidget::GameStart()
{
	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeGameOnly());
		player0->bShowMouseCursor = false;
	}

	this->SetVisibility(ESlateVisibility::Collapsed);
}
