// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameStartWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UGameStartWidget::NativeConstruct()
{
	StartButton->OnClicked.AddDynamic(this, &UGameStartWidget::GameStart);

	// 미션 설명에 관한 글을 불러오는 코드가 필요함.
	// 구글 시트나 어디선가 불러오거나 아예 그냥 밖아 넣거나 해야 할 듯
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
