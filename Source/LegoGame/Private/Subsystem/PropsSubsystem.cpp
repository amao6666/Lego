// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/PropsSubsystem.h"

const FPropsBase* UPropsSubsystem::GetPropsByID(int32 ID)
{
	if (ID < WEAPON_INDEX)
	{
		if (SkinMap.Contains(ID))
		{
			return SkinMap[ID];
		}
	}
	else
	{
		if (WeaponMap.Contains(ID))
		{
			return WeaponMap[ID];
		}
	}
	return nullptr;
}

void UPropsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//加载数据表格
	SkinDataTable = LoadObject<UDataTable>(this, TEXT("DataTable'/Game/Lego/Data/Props/DT_Skin.DT_Skin'"));
	
	const TMap<FName, uint8*> Data = SkinDataTable->GetRowMap();

	//遍历容器
	for (auto item : Data)
	{
		int ID = 0;
		FString Left, Right;
		if (item.Key.ToString().Split(TEXT("_"), &Left, &Right))
		{
			ID = FCString::Atoi(*Right) + 1;
		}
		//检查是否已经存在
		if (!SkinMap.Contains(ID))
		{
			// reinterpret_cast 强转指针类型
			SkinMap.Add(ID, reinterpret_cast<FSkin*>(item.Value));
		}
	}

	//加载武器的表格数据
	WeaponDataTable = LoadObject<UDataTable>(this, TEXT("DataTable'/Game/Lego/Data/Props/DT_Weapon.DT_Weapon'"));
	
	const TMap<FName, uint8*> WeaponData = WeaponDataTable->GetRowMap();

	//遍历容器
	for (auto item : WeaponData)
	{
		int ID = WEAPON_INDEX;
		FString Left, Right;
		if (item.Key.ToString().Split(TEXT("_"), &Left, &Right))
		{
			ID = FCString::Atoi(*Right) + 1 + WEAPON_INDEX;
		}
		//检查是否已经存在
		if (!WeaponMap.Contains(ID))
		{
			WeaponMap.Add(ID, reinterpret_cast<FWeapon*>(item.Value));
		}
	}
}
