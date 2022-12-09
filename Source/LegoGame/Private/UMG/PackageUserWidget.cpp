// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/PackageUserWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/PackageActorComponent.h"
#include "Components/SkinActorComponent.h"
#include "Player/LGPlayerCharacter.h"
#include "UMG/Widget/PackageItemUserWidget.h"
#include "UMG/Widget/PackageScrollUserWidget.h"
#include "Scene/SceneItemActor.h"
#include "Scene/PlayerModeActor.h"
#include "UMG/Widget/SkinFrameUserWidget.h"
#include "UMG/Widget/WeaponFrameUserWidget.h"

void UPackageUserWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);
	if (ALGPlayerCharacter* MyCharacter = Cast<ALGPlayerCharacter>(GetOwningPlayer()->GetPawn()))
	{
		for(auto Item : MyCharacter->GetPackageComponent()->GetNearSceneItems())
		{
			PackageScrollNearItem->AddSceneItemToScroll(Item);
		}
		MyCharacter->GetPackageComponent()->NearItemEnter.AddUObject(this, &UPackageUserWidget::OnSceneItemActorEnter);
		MyCharacter->GetPackageComponent()->NearItemLeave.AddUObject(this, &UPackageUserWidget::OnSceneItemActorLeave);
		MyCharacter->GetPackageComponent()->PackageItemAdded.AddUObject(this, &UPackageUserWidget::OnPackageItemAdded);
		MyCharacter->GetPackageComponent()->PackageItemRemoved.AddUObject(this, &UPackageUserWidget::OnPackageItemRemoved);
		MyCharacter->GetPackageComponent()->OnSkinPuton.AddUObject(this, &UPackageUserWidget::OnSkinPuton);
		MyCharacter->GetPackageComponent()->OnSkinTakeoff.AddUObject(this, &UPackageUserWidget::OnSkinTakeoff);
		MyCharacter->GetPackageComponent()->OnEquipWeapon.AddUObject(this, &UPackageUserWidget::OnEquipWeapon);
		MyCharacter->GetPackageComponent()->OnUnEquipWeapon.AddUObject(this, &UPackageUserWidget::OnUnEquipWeapon);

		//将展示角色生成，并添加到场景
		if (!PlayerModeActor)
		{
			TSubclassOf<APlayerModeActor> PlayerModeClass = LoadClass<APlayerModeActor>(nullptr, TEXT("Blueprint'/Game/Lego/Blueprint/Scene/BP_PlayerMode.BP_PlayerMode_C'"));
			PlayerModeActor = GetOwningPlayer()->GetWorld()->SpawnActor<APlayerModeActor>(PlayerModeClass, FVector(0, 0, 1000), FRotator::ZeroRotator);
			PlayerModeActor->SetSkeletalMesh(MyCharacter->GetMesh()->SkeletalMesh);
		}
		MyCharacter->GetPackageComponent()->OnSkinPuton.AddUObject(PlayerModeActor->GetSkinComponent(), &USkinActorComponent::OnSkinPuton);
		MyCharacter->GetPackageComponent()->OnSkinTakeoff.AddUObject(PlayerModeActor->GetSkinComponent(), &USkinActorComponent::OnSkinTakeoff);
		PlayerModeActor->SetActorHiddenInGame(false);
	}
}

void UPackageUserWidget::RemoveFromParent()
{
	Super::RemoveFromParent();
	if (PackageScrollNearItem)
	{
		PackageScrollNearItem->ClearChildren();	
	}
	if (GetOwningPlayer())
	{
		if (ALGPlayerCharacter* MyCharacter = Cast<ALGPlayerCharacter>(GetOwningPlayer()->GetPawn()))
		{
			MyCharacter->GetPackageComponent()->NearItemEnter.RemoveAll(this);
			MyCharacter->GetPackageComponent()->NearItemLeave.RemoveAll(this);
			MyCharacter->GetPackageComponent()->PackageItemAdded.RemoveAll(this);
			MyCharacter->GetPackageComponent()->PackageItemRemoved.RemoveAll(this);
			MyCharacter->GetPackageComponent()->OnSkinPuton.RemoveAll(this);
			MyCharacter->GetPackageComponent()->OnSkinTakeoff.RemoveAll(this);
			MyCharacter->GetPackageComponent()->OnEquipWeapon.RemoveAll(this);
			MyCharacter->GetPackageComponent()->OnUnEquipWeapon.RemoveAll(this);
			MyCharacter->GetPackageComponent()->OnSkinPuton.RemoveAll(PlayerModeActor->GetSkinComponent());
			MyCharacter->GetPackageComponent()->OnSkinTakeoff.RemoveAll(PlayerModeActor->GetSkinComponent());
			PlayerModeActor->SetActorHiddenInGame(true);
		}
	}
}

bool UPackageUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (UPackageItemUserWidget* Item = Cast<UPackageItemUserWidget>(InOperation->Payload))
	{
		if (!Item->GetSceneItemActor())
		{
			if (ALGPlayerCharacter* MyCharacter = Cast<ALGPlayerCharacter>(GetOwningPlayer()->GetPawn()))
			{
				MyCharacter->GetPackageComponent()->RemoveItemFromPackage(Item->GetSite());
				return true;
			}
		}
	}
	else if (USkinFrameUserWidget* SkinFrameWidget = Cast<USkinFrameUserWidget>(InOperation->Payload))
	{
		if (ALGPlayerCharacter* PlayerCharacter = Cast<ALGPlayerCharacter>(GetOwningPlayerPawn()))
		{
			if (PlayerCharacter->GetPackageComponent())
			{
				PlayerCharacter->GetPackageComponent()->TakeoffSkinToScreen(SkinFrameWidget->GetSkinType());
				return true;
			}
		}
	}
	else if (UWeaponFrameUserWidget* WeaponWidget = Cast<UWeaponFrameUserWidget>(InOperation->Payload))
	{
		if (ALGPlayerCharacter* PlayerCharacter = Cast<ALGPlayerCharacter>(GetOwningPlayerPawn()))
		{
			if (PlayerCharacter->GetPackageComponent())
			{
				PlayerCharacter->GetPackageComponent()->UnequipWeapon(false);
			}
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UPackageUserWidget::OnSceneItemActorEnter(ASceneItemActor* SceneItemActor)
{
	if (PackageScrollNearItem)
	{
		PackageScrollNearItem->AddSceneItemToScroll(SceneItemActor);
	}
}

void UPackageUserWidget::OnSceneItemActorLeave(ASceneItemActor* SceneItemActor)
{
	if (PackageScrollNearItem)
	{
		PackageScrollNearItem->RemoveSceneItemFromScroll(SceneItemActor);
	}
}

void UPackageUserWidget::OnPackageItemAdded(int32 Site, int32 ID)
{
	if (PackageScroll)
	{
		PackageScroll->AddSceneItemToScroll(Site, ID);
	}
}

void UPackageUserWidget::OnPackageItemRemoved(int32 Site, int32 ID)
{
	if (PackageScroll)
	{
		PackageScroll->RemoveSceneItemFromScroll(Site);
	}
}

void UPackageUserWidget::OnSkinPuton(ESkinType Type, int32 ID)
{
	for (int32 i=0; i<SkinVerticalBox->GetChildrenCount(); i++)
	{
		if (USkinFrameUserWidget* FrameWidget = Cast<USkinFrameUserWidget>(SkinVerticalBox->GetChildAt(i)))
		{
			if (FrameWidget->GetSkinType() == Type)
			{
				FrameWidget->UpdateIcon(ID);
				break;
			}
		}
	}
}

void UPackageUserWidget::OnSkinTakeoff(ESkinType Type, int32 ID)
{
	for (int32 i=0; i<SkinVerticalBox->GetChildrenCount(); i++)
	{
		if (USkinFrameUserWidget* FrameWidget = Cast<USkinFrameUserWidget>(SkinVerticalBox->GetChildAt(i)))
		{
			if (FrameWidget->GetSkinType() == Type)
			{
				FrameWidget->UpdateIcon(-1);
				break;
			}
		}
	}
}

void UPackageUserWidget::OnEquipWeapon(AWeaponActor* WeaponActor)
{
	WeaponFrameWidget->UpdateIcon(WeaponActor->GetID());
}

void UPackageUserWidget::OnUnEquipWeapon(AWeaponActor* WeaponActor)
{
	WeaponFrameWidget->UpdateIcon(-1);
}
