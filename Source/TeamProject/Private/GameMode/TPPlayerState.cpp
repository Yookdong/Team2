// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "TPGameHUD.h"

ATPPlayerState::ATPPlayerState()
{
}

void ATPPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPPlayerState, CurrentHP);
	DOREPLIFETIME(ATPPlayerState, MaxHP);
}

void ATPPlayerState::UpdateBind()
{
	APlayerController* player0 = GetWorld()->GetFirstPlayerController();

	if (player0 != nullptr)
	{
		ATPGameHUD* TPHUD = Cast<ATPGameHUD>(player0->GetHUD());

		if (TPHUD != nullptr)
		{
			TPHUD->BindPlayerState(this);
			return;
		}
	}

	FTimerManager& timermanager = GetWorldTimerManager();
	timermanager.SetTimer(TH_UpdateBind, this, &ATPPlayerState::UpdateBind, 0.1f, false);
}

void ATPPlayerState::AddDamage(float damage)
{
	CurrentHP -= damage;
	CurrentHP = FMath::Clamp(CurrentHP, 0, MaxHP);

	OnRep_CurrentHP();
}

void ATPPlayerState::Heal(float heal)
{
	CurrentHP += heal;
	CurrentHP = FMath::Clamp(CurrentHP, 0.0f, MaxHP);
	
	OnRep_CurrentHP();
}

void ATPPlayerState::SetUserName(const FString& name)
{
	UserName = name;

	OnRep_UserName();
}

void ATPPlayerState::OnRep_CurrentHP()
{
	if (Fuc_Dele_UpdateHP.IsBound())
		Fuc_Dele_UpdateHP.Broadcast(CurrentHP, MaxHP);
}

void ATPPlayerState::OnRep_MaxHP()
{
}

void ATPPlayerState::OnRep_UserName()
{
	if (Func_Dele_UpdateUserName.IsBound())
		Func_Dele_UpdateUserName.Broadcast(UserName);
}
