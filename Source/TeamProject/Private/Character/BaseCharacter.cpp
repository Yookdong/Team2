// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"
#include "Item/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/TeamProjectPlayerController.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	FolloCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FirstMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstMesh"));

	// Inherit Component
	CameraBoom->SetupAttachment(RootComponent);
	FolloCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FirstMesh->SetupAttachment(RootComponent);

	// ETC.Setting
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -89.0f), FRotator(0, 270.0f, 0));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom->SetAutoActivate(false);
	FolloCamera->SetAutoActivate(false);
	FirstMesh->SetAutoActivate(false);
	GetMesh()->SetAutoActivate(false);

	CameraBoom->SetRelativeLocation(FVector(0, 0, 50.0f));
	FirstMesh->SetRelativeLocationAndRotation(FVector(0, 0, -89.0f), FRotator(0, 270.0f, 0));

}

// 리플리케이트던 노티피던 다 등록을 해야 정상으로 작동할 수 있다.
void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, EquipItem);
}


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// 초기 시점 설정
	SetThirdView();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function
void ABaseCharacter::OpenInventory()
{
}

void ABaseCharacter::SetFirstView()
{
	if (bIsFirstCam == true) return;

	bIsFirstCam = true;

	FirstMesh->SetVisibility(true);

	// 1인칭 캠 및 메시
	GetMesh()->SetOwnerNoSee(true);

	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->SocketOffset = FVector::Zero();

	FirstMesh->SetOnlyOwnerSee(true);
	FirstMesh->bCastDynamicShadow = false;
	FirstMesh->CastShadow = false;

	bUseControllerRotationYaw = true;
}

void ABaseCharacter::SetThirdView()
{
	if (bIsFirstCam == false) return;

	bIsFirstCam = false;

	FirstMesh->SetVisibility(false);

	// 3인칭 캠 및 메시
	GetMesh()->SetOwnerNoSee(false);

	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0, 50.0f, 50.0f);

	FirstMesh->SetOnlyOwnerSee(false);
	FolloCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
}

// Client to Server
void ABaseCharacter::ReqPressF_Implementation()
{
	OnRep_EquipItem();
}

// Server to Client
void ABaseCharacter::OnRep_EquipItem()
{
	IItemInterface* interfaceOBJ = Cast<IItemInterface>(EquipItem);

	if (interfaceOBJ != nullptr)
	{
		interfaceOBJ->Execute_EventGetItem(EquipItem);
	}
}



//////////////////////////////////////////////////////////////////////////
// Input

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);

		//Trigger
		EnhancedInputComponent->BindAction(TriggerAction, ETriggerEvent::Started, this, &ABaseCharacter::Trigger);

		//PressF
		EnhancedInputComponent->BindAction(PressFAction, ETriggerEvent::Started, this, &ABaseCharacter::PressF);

		//PressI
		EnhancedInputComponent->BindAction(PressIAction, ETriggerEvent::Started, this, &ABaseCharacter::PressI);

		//ViewChange
		EnhancedInputComponent->BindAction(ViewChangeAction, ETriggerEvent::Started, this, &ABaseCharacter::ViewChange);
	}

}

void ABaseCharacter::Move(const FInputActionValue& value)
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

void ABaseCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(lookAxisVector.Y);
	}
}

void ABaseCharacter::Trigger(const FInputActionValue& value)
{
}

void ABaseCharacter::PressF(const FInputActionValue& value)
{
}

void ABaseCharacter::PressI(const FInputActionValue& value)
{
}

void ABaseCharacter::ViewChange(const FInputActionValue& value)
{
	if (bIsFirstCam)
	{
		SetThirdView();
	}
	else
	{
		SetFirstView();
	}
}
