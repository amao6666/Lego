// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PackageActorComponent.h"
#include "Character/LGCharacterBase.h"
#include "Scene/SceneItemActor.h"
#include "Weapon/WeaponActor.h"

AWeaponActor* UPackageActorComponent::GetHoldWeapon()
{
	return HoldWeapon;
}

// Sets default values for this component's properties
UPackageActorComponent::UPackageActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPackageActorComponent::AddNearSceneItem(ASceneItemActor* SceneItemActor)
{
	NearSceneItems.Add(SceneItemActor);
	if (NearItemEnter.IsBound())
	{
		NearItemEnter.Broadcast(SceneItemActor);
	}
}

void UPackageActorComponent::RemoveNearSceneItem(ASceneItemActor* SceneItemActor)
{
	NearSceneItems.Remove(SceneItemActor);
	if (NearItemLeave.IsBound())
	{
		NearItemLeave.Broadcast(SceneItemActor);
	}
}


// Called when the game starts
void UPackageActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

int32 UPackageActorComponent::GetFreeSite()
{
	int32 Site = 0;
	while (Package.Contains(Site))
	{
		Site++;
	}
	return Site;
}

void UPackageActorComponent::SpawnNearSceneItemActor(int32 OutID)
{
	if (ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(GetOwner()))
	{
		FTransform Transform;
		FVector TempLocation = CharacterBase->GetActorLocation();
		TempLocation.X += 200;
		Transform.SetLocation(TempLocation);
		ASceneItemActor* SceneItemActor = GetWorld()->SpawnActorDeferred<ASceneItemActor>(ASceneItemActor::StaticClass(), Transform);
		SceneItemActor->SetID(OutID);
		SceneItemActor->FinishSpawning(Transform);
	}
}

// Called every frame
void UPackageActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<ASceneItemActor*> UPackageActorComponent::GetNearSceneItems()
{
	return NearSceneItems;
}

void UPackageActorComponent::AddItemToPackage(ASceneItemActor* SceneItemActor)
{
	if (SceneItemActor) SceneItemActor->Destroy();
	AddItemToPackage(SceneItemActor->GetID());
}

void UPackageActorComponent::AddItemToPackage(int32 SceneID)
{
	int32 Site = GetFreeSite();
	Package.Add(Site, SceneID);
	if (PackageItemAdded.IsBound())
	{
		PackageItemAdded.Broadcast(Site, SceneID);
	}
}

void UPackageActorComponent::RemoveItemFromPackage(int32 Site, bool bSpawnSceneItem)
{
	if (PackageItemRemoved.IsBound())
	{
		if (Package.Contains(Site))
		{
			PackageItemRemoved.Broadcast(Site, Package[Site]);
		}
		if (bSpawnSceneItem)
		{
			SpawnNearSceneItemActor(Package[Site]);
		}
	}
}

void UPackageActorComponent::PutonSkin(ASceneItemActor* SceneItemActor, ESkinType SkinType)
{
	if (!SceneItemActor)
	{
		return;
	}
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UPropsSubsystem>()->GetPropsByID(SceneItemActor->GetID());
	if (!PropsBase)
	{
		return;
	}
	if (PropsBase->Type != EPropsType::EPT_Skin)
	{
		return;
	}
	//??????????????????
	const FSkin* SkinInfo = static_cast<const FSkin*>(PropsBase);
	if (SkinType != ESkinType::EST_None)
	{
		if (SkinType != SkinInfo->SkinType)
		{
			return;
		}
	}
	SkinType = SkinInfo->SkinType;

	//???????????????????????????????????????????????????
	TakeoffSkin(SkinType, false);

	//????????????
	SkinsMap.Add(SkinType, SceneItemActor->GetID());

	//????????????
	if (OnSkinPuton.IsBound())
	{
		OnSkinPuton.Broadcast(SkinType, SceneItemActor->GetID());
	}
	SceneItemActor->Destroy();
}

void UPackageActorComponent::PutonSkin(int32 Site, ESkinType SkinType)
{
	if (!Package.Contains(Site))
	{
		return;
	}
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UPropsSubsystem>()->GetPropsByID(Package[Site]);
	if (!PropsBase)
	{
		return;
	}
	if (PropsBase->Type != EPropsType::EPT_Skin)
	{
		return;
	}
	//??????????????????
	const FSkin* SkinInfo = static_cast<const FSkin*>(PropsBase);
	if (SkinType != ESkinType::EST_None)
	{
		if (SkinType != SkinInfo->SkinType)
		{
			return;
		}
	}
	SkinType = SkinInfo->SkinType;

	//???????????????????????????????????????????????????
	TakeoffSkin(SkinType, false);

	//????????????
	SkinsMap.Add(SkinType, Package[Site]);

	//????????????
	if (OnSkinPuton.IsBound())
	{
		OnSkinPuton.Broadcast(SkinType, Package[Site]);
	}

	//?????????????????????
	RemoveItemFromPackage(Site, false);
}

void UPackageActorComponent::TakeoffSkin(ESkinType Type, bool bUpdateSkin)
{
	if (SkinsMap.Contains(Type))//??????????????????
	{
		AddItemToPackage(SkinsMap[Type]);
		if (bUpdateSkin)
		{
			if (OnSkinTakeoff.IsBound())
			{
				OnSkinTakeoff.Broadcast(Type, SkinsMap[Type]);
			}
		}
		SkinsMap.Remove(Type);
	}
}

void UPackageActorComponent::TakeoffSkinToScreen(ESkinType Type)
{
	if (SkinsMap.Contains(Type))
	{
		SpawnNearSceneItemActor(SkinsMap[Type]);
		if (OnSkinTakeoff.IsBound())
		{
			OnSkinTakeoff.Broadcast(Type, -1);
		}
		SkinsMap.Remove(Type);
	}	
}

void UPackageActorComponent::EquipWeapon(ASceneItemActor* SceneItemActor)
{
	if (EquipWeaponByPropsID(SceneItemActor->GetID()))
	{
		SceneItemActor->Destroy();
	}
}

void UPackageActorComponent::EquipWeapon(int32 Site)
{
	if (Package.Contains(Site))
	{
		if (EquipWeaponByPropsID(Package[Site]))
		{
			RemoveItemFromPackage(Site, false);
		}
	}
}

bool UPackageActorComponent::EquipWeaponByPropsID(int32 ID)
{
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UPropsSubsystem>()->GetPropsByID(ID);
	if (!PropsBase || PropsBase->Type != EPropsType::EPT_Weapon)
	{
		return false;
	}
	const FWeapon* WeaponInfo = static_cast<const FWeapon*>(PropsBase);
	if (HoldWeapon) UnequipWeapon(true);
	//????????????
	HoldWeapon = GetOwner()->GetWorld()->SpawnActor<AWeaponActor>(WeaponInfo->WeaponClass);
	HoldWeapon->SetID(ID);
	//??????????????????
	HoldWeapon->SetMaster(Cast<ALGCharacterBase>(GetOwner()));
	if (OnEquipWeapon.IsBound())
	{
		OnEquipWeapon.Broadcast(HoldWeapon);
	}
	ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(GetOwner());
	if (CharacterBase) CharacterBase->SetBlockView(true);
	return true;
}

void UPackageActorComponent::UnequipWeapon(bool bPackage)
{
	if (HoldWeapon)
	{
		bPackage ? AddItemToPackage(HoldWeapon->GetID()) : SpawnNearSceneItemActor(HoldWeapon->GetID());
		HoldWeapon->Destroy();
		HoldWeapon = nullptr;
		if (OnUnEquipWeapon.IsBound())
		{
			OnUnEquipWeapon.Broadcast(nullptr);
		}
		ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(GetOwner());
		if (CharacterBase) CharacterBase->SetBlockView(false);
	}
}

