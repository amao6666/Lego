// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Subsystem/PropsSubsystem.h"
#include "PackageActorComponent.generated.h"

class ASceneItemActor;
class AWeaponActor;

DECLARE_MULTICAST_DELEGATE_OneParam(NotifyNearItemChange, ASceneItemActor*);
DECLARE_MULTICAST_DELEGATE_TwoParams(NotifyPackageItemChange, int32, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(NotifySkinUpdate, ESkinType, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(NotifyWeaponChanged, AWeaponActor*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEGOGAME_API UPackageActorComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY()
	TArray<ASceneItemActor*> NearSceneItems;

	TMap<int32, int32> Package;
	TMap<ESkinType, int32> SkinsMap;

	int32 GetFreeSite();
	void SpawnNearSceneItemActor(int32 OutID);
	
public:
	NotifyNearItemChange NearItemEnter;
	NotifyNearItemChange NearItemLeave;

	NotifyPackageItemChange PackageItemAdded;
	NotifyPackageItemChange PackageItemRemoved;

	//通知皮肤穿上了
	NotifySkinUpdate OnSkinPuton;
	//通知皮肤脱下了
	NotifySkinUpdate OnSkinTakeoff;

	// 武器通知
	NotifyWeaponChanged OnEquipWeapon;
	NotifyWeaponChanged OnUnEquipWeapon;

	UPROPERTY()
	AWeaponActor* HoldWeapon;
	AWeaponActor* GetHoldWeapon();
	
	// Sets default values for this component's properties
	UPackageActorComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<ASceneItemActor*> GetNearSceneItems();

	void AddNearSceneItem(ASceneItemActor* SceneItemActor);
	void RemoveNearSceneItem(ASceneItemActor* SceneItemActor);
	
	void AddItemToPackage(ASceneItemActor* SceneItemActor);
	void AddItemToPackage(int32 SceneID);
	void RemoveItemFromPackage(int32 Site, bool bSpawnSceneItem = true);

	//穿脱皮肤
	void PutonSkin(ASceneItemActor* SceneItemActor, ESkinType SkinType = ESkinType::EST_None);
	void PutonSkin(int32 Site, ESkinType SkinType = ESkinType::EST_None);
	void TakeoffSkin(ESkinType Type, bool bUpdateSkin = true);
	void TakeoffSkinToScreen(ESkinType Type);

	//装备武器
	void EquipWeapon(ASceneItemActor* SceneItemActor);
	bool EquipWeaponByPropsID(int32 ID);
	void EquipWeapon(int32 Site);
	void UnequipWeapon(bool bPackage = true);
};
