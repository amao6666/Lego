// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Subsystem/PropsSubsystem.h"
#include "PackageUserWidget.generated.h"

class ASceneItemActor;
class UPackageScrollUserWidget;
class APlayerModeActor;
class UWeaponFrameUserWidget;

/**
 * 
 */
UCLASS()
class LEGOGAME_API UPackageUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
	virtual void RemoveFromParent() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UPackageScrollUserWidget* PackageScrollNearItem;

	UPROPERTY(meta=(BindWidget))
	UPackageScrollUserWidget* PackageScroll;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* SkinVerticalBox;
	
	UPROPERTY(meta=(BindWidget))
	UWeaponFrameUserWidget* WeaponFrameWidget;

	UPROPERTY()
	APlayerModeActor* PlayerModeActor;
	
	void OnSceneItemActorEnter(ASceneItemActor* SceneItemActor);
	void OnSceneItemActorLeave(ASceneItemActor* SceneItemActor);

	void OnPackageItemAdded(int32 Site, int32 ID);
	void OnPackageItemRemoved(int32 Site, int32 ID);

	void OnSkinPuton(ESkinType Type, int32 ID);
	void OnSkinTakeoff(ESkinType Type, int32 ID);

	void OnEquipWeapon(AWeaponActor* WeaponActor);
	void OnUnEquipWeapon(AWeaponActor* WeaponActor);

public:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
