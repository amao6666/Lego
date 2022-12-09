// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Weapon/WeaponActor.h"
#include "PropsSubsystem.generated.h"

UENUM()
enum class EPropsType : uint8
{
	EPT_Skin,
	EPT_Weapon
};

UENUM()
enum class ESkinType : uint8
{
	EST_None,
	EST_Hair,
	EST_Glasses,
	EST_Helmet,
	EST_Facemask,
	EST_Bag,
	EST_Eyeshades,
	EST_Coat,
	EST_Beard
};

UENUM()
enum class EGender : uint8
{
	EG_Male,
	EG_Female
};

USTRUCT()
struct FPropsBase : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	int32 ID;
	UPROPERTY(EditAnywhere)
	FText Name;
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	
	EPropsType Type;
};

#define WEAPON_INDEX 100

USTRUCT()
struct FSkin : public FPropsBase
{
	GENERATED_BODY()

	FSkin(): StaticMesh(nullptr), SkeletalMesh(nullptr), SkinType(ESkinType::EST_None), Gender(EGender::EG_Male)
	{
		Type = EPropsType::EPT_Skin;
	}
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere)
	ESkinType SkinType;
	UPROPERTY(EditAnywhere)
	EGender Gender;
};

USTRUCT()
struct FWeapon : public FPropsBase
{
	GENERATED_BODY()

	FWeapon(): WeaponMesh(nullptr)
	{
		Type = EPropsType::EPT_Weapon;
	}

	UPROPERTY(EditAnywhere)
	USkeletalMesh* WeaponMesh;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeaponActor> WeaponClass;
};

/**
 * 
 */
UCLASS()
class LEGOGAME_API UPropsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	const FPropsBase* GetPropsByID(int32 ID);
	
protected:
	UPROPERTY()
	UDataTable* SkinDataTable;

	UPROPERTY()
	UDataTable* WeaponDataTable;
	
	TMap<int32, FSkin*> SkinMap;
	TMap<int32, FWeapon*> WeaponMap;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
