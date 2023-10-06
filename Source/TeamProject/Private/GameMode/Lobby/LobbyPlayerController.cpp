// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Lobby/LobbyPlayerController.h"
#include "GameMode/TPGameInstance.h"
#include "TPLobbyPlayerState.h"

ALobbyPlayerController::ALobbyPlayerController()
{
}

void ALobbyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	ResClientPossess();
}

void ALobbyPlayerController::ResClientPossess_Implementation()
{
	UTPGameInstance* gameinst = Cast<UTPGameInstance>(GetGameInstance());

	if (gameinst != nullptr)
	{
		FString name = gameinst->GetUserName();

		ReqChangeUserName(name);
	}
}

void ALobbyPlayerController::ReqChangeUserName_Implementation(const FString& name)
{
	ATPLobbyPlayerState* lobbyPS = Cast<ATPLobbyPlayerState>(PlayerState);

	if (lobbyPS != nullptr)
	{
		lobbyPS->SetUserName(name);
	}
}
