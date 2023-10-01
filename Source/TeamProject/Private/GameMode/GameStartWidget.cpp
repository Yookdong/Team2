// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameStartWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Net/UnrealNetwork.h"

void UGameStartWidget::NativeConstruct()
{
	StartButton->OnClicked.AddDynamic(this, &UGameStartWidget::GameStart);

	// 미션 설명에 관한 글을 불러오는 코드가 필요함.
	// 구글 시트나 어디선가 불러오거나 아예 그냥 밖아 넣거나 해야 할 듯

	bIsStart = false;
}

void UGameStartWidget::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UGameStartWidget, bIsStart);
}

void UGameStartWidget::GameStart()
{
	UE_LOG(LogTemp, Display, TEXT("PressButton"));
	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0))
	{
		player0->SetInputMode(FInputModeGameOnly());
		player0->bShowMouseCursor = false;
	}

	bIsStart = true;

	OnRep_bIsStart();

	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UGameStartWidget::OnRep_bIsStart()
{
	UE_LOG(LogTemp, Display, TEXT("Bindinginginging"));
	if (Fuc_Dele_IsStart.IsBound())
		Fuc_Dele_IsStart.Broadcast();
}
