// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissionController.generated.h"

UCLASS()
class TEAMPROJECT_API AMissionController : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsClear;

public:	
	// Sets default values for this actor's properties
	AMissionController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void OpenDoor() { bIsClear = true; }

	// Client to Server
	UFUNCTION(Server, Reliable)
	void ReqAddScore();

};
