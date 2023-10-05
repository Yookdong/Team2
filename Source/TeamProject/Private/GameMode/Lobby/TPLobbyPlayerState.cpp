#include "GameMode/Lobby/TPLobbyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "LobbyHUD.h"

ATPLobbyPlayerState::ATPLobbyPlayerState()
{
}

void ATPLobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPLobbyPlayerState, UserName);
}

void ATPLobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UpdateBind();
}

void ATPLobbyPlayerState::SetUserName(const FString& name)
{
	UserName = name;

	OnRep_UserName();
}

void ATPLobbyPlayerState::OnRep_UserName()
{
	if (Func_Dele_UpdateUserName.IsBound())
		Func_Dele_UpdateUserName.Broadcast(UserName);
}

void ATPLobbyPlayerState::UpdateBind()
{
	APlayerController* player0 = GetWorld()->GetFirstPlayerController();

	if (player0 != nullptr)
	{
		ALobbyHUD* lobbyhud = Cast<ALobbyHUD>(player0->GetHUD());

		if (lobbyhud != nullptr)
		{
			lobbyhud->BindMyPlayerState(this);
			return;
		}
	}

	FTimerManager& timermanager = GetWorldTimerManager();
	timermanager.SetTimer(TH_UpdateBind, this, &ATPLobbyPlayerState::UpdateBind, 0.1f, false);
}
