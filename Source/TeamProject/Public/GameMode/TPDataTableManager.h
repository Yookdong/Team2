// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TPDataTableManager.generated.h"


// About GameState
UENUM(BlueprintType)
enum class EGAMESTATE : uint8
{
	Entry UMETA(DisplayName = "Entry"),
	Lobby UMETA(DisplayName = "Lobby"),
	GameStart UMETA(DisplayName = "GameStart"),
	GamePlay UMETA(DisplayName = "GamePlay"),
	GameEnd UMETA(DisplayName = "GameEnd"),
	Loading UMETA(DisplayName = "Loading"),
};


// About Item
UENUM(BlueprintType)
enum class EITEMTYPE : uint8
{
	IT_Basic UMETA(DisplayName = "Basic"),
	IT_Utility UMETA(DisplayName = "Utility"),
	IT_Intall UMETA(DisplayName = "Install"),
	IT_Weapon UMETA(DisplayName = "Weapon"),
};

UENUM(BlueprintType)
enum class ESUBTYPE : uint8
{
	IT_Basic UMETA(DisplayName = "Basic"),
	IT_Light UMETA(DisplayName = "Light"),
	IT_Key UMETA(DisplayName = "Key"),
	IT_Tool UMETA(DisplayName = "Tool"),
};

USTRUCT(BlueprintType)
struct FST_Item :public FTableRowBase
{
	GENERATED_BODY()

public:	
    FST_Item() : ItemMainType(EITEMTYPE::IT_Basic), ItemSubType(ESUBTYPE::IT_Basic), ItemMesh(nullptr), ItemEffect(nullptr), ItemSound(nullptr), ItemClass(nullptr), TriigerAnimMontage(nullptr), Name(FText()), Description(FText()), Thumbnail(nullptr), StackSize(0) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EITEMTYPE ItemMainType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	ESUBTYPE ItemSubType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	class UParticleSystem* ItemEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	class USoundBase* ItemSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseClass)
	TSubclassOf<class AItemBase> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimMontage)
	class UAnimMontage* TriigerAnimMontage;

	// about jh
	//----------------------------------------------------------------------

	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FText Name;

	// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FText Description;

	// 아이템 썸네일 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	class UTexture2D* Thumbnail;

	// 아이템 스택 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 StackSize;

};

USTRUCT(BlueprintType)
struct FST_Slot :public FTableRowBase
{
	GENERATED_BODY()

public:
	FST_Slot() :ItemID(FName()), Quantity(0) {}

	// 아이템 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot)
	FName ItemID;

	// 아이템 수량
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot)
	int32 Quantity;
};

//여기까지가 JH 추가부분
//------------------------------------------------------------------------------

// About Character
UENUM(BlueprintType)
enum class ECHARTYPE : uint8
{
	White UMETA(DisplayName = "White"),
	Red UMETA(DisplayName = "Red"),
	Green UMETA(DisplayName = "Green"),
	IT_Blue UMETA(DisplayName = "Blue"),
};

USTRUCT(BlueprintType)
struct FST_Character :public FTableRowBase
{
	GENERATED_BODY()
public:
	FST_Character() : BodyMaterial(nullptr), ArmMaterial(nullptr), CharacterIcon(nullptr) {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Material)
	class UMaterialInterface* BodyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Material)
	class UMaterialInterface* ArmMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Image)
	class UImage* CharacterIcon;
};



/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UTPDataTableManager : public UDataTable
{
	GENERATED_BODY()
	
};
