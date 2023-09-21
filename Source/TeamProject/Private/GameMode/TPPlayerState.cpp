// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "TPGameHUD.h"

ATPPlayerState::ATPPlayerState()
{
	MaxHP = 100;
	CurrentHP = MaxHP;
	MaxOX = 100;
	CurrentOX = MaxOX;
}

void ATPPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPPlayerState, CurrentHP);
	DOREPLIFETIME(ATPPlayerState, MaxHP);
	DOREPLIFETIME(ATPPlayerState, CurrentOX);
	DOREPLIFETIME(ATPPlayerState, MaxOX);
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

void ATPPlayerState::UseOX(float ox)
{
	CurrentOX -= ox;
	CurrentOX = FMath::Clamp(CurrentOX, 0, MaxOX);

	OnRep_CurrentOX();
}

void ATPPlayerState::ChargeOX(float ox)
{
	CurrentOX += ox;
	CurrentOX = FMath::Clamp(CurrentOX, 0.0f, MaxOX);

	OnRep_CurrentOX();
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

void ATPPlayerState::OnRep_CurrentOX()
{
	if (Fuc_Dele_UpdateOX.IsBound())
		Fuc_Dele_UpdateOX.Broadcast(CurrentOX, MaxOX);
}

void ATPPlayerState::OnRep_MaxOX()
{
}

void ATPPlayerState::OnRep_UserName()
{
	if (Func_Dele_UpdateUserName.IsBound())
		Func_Dele_UpdateUserName.Broadcast(UserName);
}
