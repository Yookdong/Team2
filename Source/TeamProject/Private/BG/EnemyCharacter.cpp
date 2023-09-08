// Fill out your copyright notice in the Description page of Project Settings.


#include "BG/EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &AEnemyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &AEnemyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &AEnemyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	


}

void AEnemyCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AEnemyCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AEnemyCharacter::Attact()
{
	UE_LOG(LogTemp, Display, TEXT("Attact!!!"));
}



