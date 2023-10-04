// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameMode/TPPlayerController.h"
#include "GameMode/TPDataTableManager.h"
#include "GameMode/TPGameInstance.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"
#include "GameMode/TPPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATPBaseCharacter::ATPBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	FolloCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FirstMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstMesh"));
	MapCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MapCameraBoom"));
	MiniMapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMapCapture"));
	IconforMiniMap = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("IconforMiniMap"));

	// Inherit Component
	CameraBoom->SetupAttachment(RootComponent);
	FolloCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FirstMesh->SetupAttachment(RootComponent);
	MapCameraBoom->SetupAttachment(RootComponent);
	MiniMapCapture->SetupAttachment(MapCameraBoom);
	IconforMiniMap->SetupAttachment(GetMesh());

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
	MapCameraBoom->SetRelativeRotation(FRotator(-90.0f, 0, 0));
	MapCameraBoom->TargetArmLength = 700.0f;
	MapCameraBoom->bUsePawnControlRotation = false;
	MapCameraBoom->bInheritPitch = false;
	MapCameraBoom->bInheritRoll = false;
	MapCameraBoom->bInheritYaw = false;

	MiniMapCapture->bAutoActivate = false;
	MiniMapCapture->ProjectionType = ECameraProjectionMode::Orthographic; // 미니맵 평면인가 3D인가 조절
	MiniMapCapture->OrthoWidth = 2000.0f; // 미니맵 시야 각 조절

	SetFirstView();
}

void ATPBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPBaseCharacter, EquipItem);
}

// Called when the game starts or when spawned
void ATPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UTPGameInstance* gameinst = Cast<UTPGameInstance>(GetGameInstance());

	if (gameinst != nullptr)
	{
		CharacterData = gameinst->GetCharacterRowData();

		if (CharacterData != nullptr)
			SetCharacter();
	}

	BindPlayerState();
}

float ATPBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (EventInstigator != nullptr)
	{
		ATPPlayerState* playerstate = Cast<ATPPlayerState>(GetPlayerState());
		if (IsValid(playerstate))
		{
			playerstate->AddDamage(DamageAmount);
			return DamageAmount;
		}
	}

	return 0;
}

// Called every frame
void ATPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATPBaseCharacter::BindPlayerState()
{
	ATPPlayerState* playerstate = Cast<ATPPlayerState>(GetPlayerState());

	if (IsValid(playerstate))
	{
		playerstate->Fuc_Dele_UpdateHP.AddDynamic(this, &ATPBaseCharacter::EventUpdateHP);
		EventUpdateHP(playerstate->CurrentHP, playerstate->MaxHP);

		playerstate->Fuc_Dele_UpdateOX.AddDynamic(this, &ATPBaseCharacter::EventUpdateOX);
		EventUpdateOX(playerstate->CurrentOX, playerstate->MaxOX);

		return;
	}

	GetWorldTimerManager().SetTimer(TH_BindPlayerState, this, &ATPBaseCharacter::BindPlayerState, 0.1f, false);
}

void ATPBaseCharacter::ChargeOX(float value)
{
	ATPPlayerState* playerstate = Cast<ATPPlayerState>(GetPlayerState());

	if (IsValid(playerstate))
	{
		playerstate->ChargeOX(value);
	}
}

void ATPBaseCharacter::MinusHP()
{
	UGameplayStatics::ApplyDamage(this, 1.0f, GetController(), this, UDamageType::StaticClass());
}

void ATPBaseCharacter::Heal(float value)
{
	ATPPlayerState* playerstate = Cast<ATPPlayerState>(GetPlayerState());

	if (IsValid(playerstate))
	{
		playerstate->Heal(value);
	}
}

//void ATPBaseCharacter::SetThirdView()
//{
//	FirstMesh->SetVisibility(false);
//
//	GetMesh()->SetOwnerNoSee(false);
//
//	bUseControllerRotationYaw = false;
//
//	CameraBoom->TargetArmLength = 350.0f;
//	CameraBoom->SocketOffset = FVector(0, 50.0f, 50.0f);
//
//	FirstMesh->SetOnlyOwnerSee(false);
//	FolloCamera->bUsePawnControlRotation = false;
//
//	GetCharacterMovement()->bOrientRotationToMovement = true;
//}

void ATPBaseCharacter::SetFirstView()
{
	FirstMesh->SetVisibility(true);

	// 1인칭 캠 및 메시
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

void ATPBaseCharacter::SetCharacter()
{
	GetMesh()->SetMaterial(0, CharacterData->BodyMaterial);
	FirstMesh->SetMaterial(0, CharacterData->ArmMaterial);
}

// 연결
void ATPBaseCharacter::EventUpdateHP_Implementation(float curhp, float maxhp)
{
	if (curhp <= 0)
	{
		if (HasAuthority())
		{
			ReqDie();
		}
	}
}

void ATPBaseCharacter::EventUpdateOX_Implementation(float curox, float maxox)
{
	if (curox <= 0)
	{
		if (HasAuthority())
		{
			MinusHP(); 
			GetWorldTimerManager().SetTimer(TH_OXZero, this, &ATPBaseCharacter::MinusHP, 1.0f, false);
		}
	}
}

// Client to Server
void ATPBaseCharacter::ReqDie_Implementation()
{
	ResDie();
}

// Server to Client
void ATPBaseCharacter::OnRep_EquipItem()
{
}

void ATPBaseCharacter::ResDie_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
}

//================= Input ==============================
void ATPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ATPPlayerController* ps = Cast<ATPPlayerController>(Controller);
	if (ps)
		ps->SetupInactiveStateInputComponent(PlayerInputComponent); // 이게 맞나........??

	// Set up action bindings
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Display, TEXT("Input Binding"));

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPBaseCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPBaseCharacter::Look);

		//ViewChange
		//EnhancedInputComponent->BindAction(ViewChangeAction, ETriggerEvent::Started, this, &ATPBaseCharacter::ViewChange);
	}

}

void ATPBaseCharacter::Move(const FInputActionValue& value)
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

void ATPBaseCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(lookAxisVector.Y);
	}
}

//void ATPBaseCharacter::ViewChange(const FInputActionValue& value)
//{
//	if (Controller != nullptr)
//	{
//		ATPPlayerController* ps = Cast<ATPPlayerController>(Controller);
//		
//		if (IsValid(ps))
//		{
//			if (ps->bGetThirdView())
//			{
//				GetController()->SetControlRotation(GetActorRotation());
//				SetFirstView();
//				ps->bSetThirdView(false);
//			}
//			else
//			{
//				GetController()->SetControlRotation(CameraBoom->GetDesiredRotation());
//				SetThirdView();
//				ps->bSetThirdView(true);
//			}
//		}
//	}
//}