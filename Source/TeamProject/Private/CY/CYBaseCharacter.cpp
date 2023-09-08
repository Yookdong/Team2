// Fill out your copyright notice in the Description page of Project Settings.


#include "CY/CYBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "CY/CYPlayerController.h"
#include "GameMode/TPDataTableManager.h"
#include "GameMode/TPGameInstance.h"

// Sets default values
ACYBaseCharacter::ACYBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	FolloCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FirstMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstMesh"));
	MapCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MapCameraBoom"));
	MiniMapCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MiniMapCamera"));

	// Inherit Component
	CameraBoom->SetupAttachment(RootComponent);
	FolloCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FirstMesh->SetupAttachment(RootComponent);

	// ETC.Setting
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0, 720.0f, 0);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -94.0f), FRotator(0, 270.0f, 0));
	FirstMesh->SetRelativeLocationAndRotation(FVector(0, 0, -94.0f), FRotator(0, 270.0f, 0));

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	FirstMesh->SetAutoActivate(false);
	GetMesh()->SetAutoActivate(false);

	CameraBoom->SetRelativeLocation(FVector(0, 0, 50.0f));
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritRoll = true;
	CameraBoom->bInheritYaw = true;

	MapCameraBoom->bAutoActivate = false;
	MiniMapCamera->bAutoActivate = false;

	SetThirdView();
}

// Called when the game starts or when spawned
void ACYBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Display, TEXT("Char BeginPlay"));

	UTPGameInstance* gameinst = Cast<UTPGameInstance>(GetGameInstance());

	if (gameinst != nullptr)
	{
		CharacterData = gameinst->GetCharacterRowData();

		if (CharacterData != nullptr)
			SetCharacter();
	}

}

// Called every frame
void ACYBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACYBaseCharacter::SetThirdView()
{
	UE_LOG(LogTemp, Display, TEXT("SetThirdView"));

	FirstMesh->SetVisibility(false);

	GetMesh()->SetOwnerNoSee(false);

	bUseControllerRotationYaw = false;

	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->SocketOffset = FVector(0, 50.0f, 50.0f);

	FirstMesh->SetOnlyOwnerSee(false);
	FolloCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACYBaseCharacter::SetFirstView()
{
	UE_LOG(LogTemp, Display, TEXT("SetFirstView"));

	FirstMesh->SetVisibility(true);

	// 1ÀÎÄª Ä· ¹× ¸Þ½Ã
	GetMesh()->SetOwnerNoSee(true);

	bUseControllerRotationYaw = true;

	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->SocketOffset = FVector(0, 0, 20.0f);

	FolloCamera->bUsePawnControlRotation = true;

	FirstMesh->SetOnlyOwnerSee(true);
	FirstMesh->bCastDynamicShadow = false;
	FirstMesh->CastShadow = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACYBaseCharacter::SetCharacter()
{
	GetMesh()->SetMaterial(0, CharacterData->BodyMaterial);
	FirstMesh->SetMaterial(0, CharacterData->ArmMaterial);
}

//================= Input ==============================
void ACYBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Display, TEXT("Input Binding"));

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACYBaseCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACYBaseCharacter::Look);

		//Trigger
		EnhancedInputComponent->BindAction(TriggerAction, ETriggerEvent::Started, this, &ACYBaseCharacter::Trigger);

		//PressF
		EnhancedInputComponent->BindAction(PressFAction, ETriggerEvent::Started, this, &ACYBaseCharacter::PressF);

		//PressI
		EnhancedInputComponent->BindAction(PressIAction, ETriggerEvent::Started, this, &ACYBaseCharacter::PressI);

		//ViewChange
		EnhancedInputComponent->BindAction(ViewChangeAction, ETriggerEvent::Started, this, &ACYBaseCharacter::ViewChange);
	}

}

void ACYBaseCharacter::Move(const FInputActionValue& value)
{
	FVector2D movementVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

		const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forwardDirection, movementVector.Y);
		AddMovementInput(rightDirection, movementVector.X);
	}
}

void ACYBaseCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(lookAxisVector.Y);
	}
}

void ACYBaseCharacter::Trigger(const FInputActionValue& value)
{
}

void ACYBaseCharacter::PressF(const FInputActionValue& value)
{
}

void ACYBaseCharacter::PressI(const FInputActionValue& value)
{
}

void ACYBaseCharacter::ViewChange(const FInputActionValue& value)
{
	if (Controller != nullptr)
	{
		ACYPlayerController* ps = Cast<ACYPlayerController>(Controller);
		
		if (IsValid(ps))
		{
			if (ps->bGetThirdView())
			{
				GetController()->SetControlRotation(GetActorRotation());
				SetFirstView();
				ps->bSetThirdView(false);
			}
			else
			{
				GetController()->SetControlRotation(CameraBoom->GetDesiredRotation());
				SetThirdView();
				ps->bSetThirdView(true);
			}
		}
	}
}