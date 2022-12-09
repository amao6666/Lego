// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Widget/PackageScrollUserWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/PackageActorComponent.h"
#include "Player/LGPlayerCharacter.h"
#include "UMG/Widget/PackageItemUserWidget.h"
#include "Scene/SceneItemActor.h"
#include "UMG/Widget/SkinFrameUserWidget.h"
#include "UMG/Widget/WeaponFrameUserWidget.h"

void UPackageScrollUserWidget::AddSceneItemToScroll(ASceneItemActor* ItemActor)
{
	TSubclassOf<UPackageItemUserWidget> PackageItemClass = LoadClass<UPackageItemUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Lego/UMG/Widget/Widget_PackageItem.Widget_PackageItem_C'"));
	UPackageItemUserWidget* PackageItem = CreateWidget<UPackageItemUserWidget>(GetOwningPlayer(), PackageItemClass);
	PackageItem->SetItemInfo(ItemActor);
	ScrollBox->AddChild(PackageItem);
}

void UPackageScrollUserWidget::AddSceneItemToScroll(int32 OutSite, int32 ID)
{
	TSubclassOf<UPackageItemUserWidget> PackageItemClass = LoadClass<UPackageItemUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Lego/UMG/Widget/Widget_PackageItem.Widget_PackageItem_C'"));
	UPackageItemUserWidget* PackageItem = CreateWidget<UPackageItemUserWidget>(GetOwningPlayer(), PackageItemClass);
	PackageItem->SetSite(OutSite);
	PackageItem->SetItemInfo(ID);
	ScrollBox->AddChild(PackageItem);
}

void UPackageScrollUserWidget::RemoveSceneItemFromScroll(ASceneItemActor* ItemActor)
{
	for (int32 i = 0; i < ScrollBox->GetChildrenCount(); i++)
	{
		if (UPackageItemUserWidget* Item = Cast<UPackageItemUserWidget>(ScrollBox->GetChildAt(i)))
		{
			if (Item->GetSceneItemActor() == ItemActor)
			{
				ScrollBox->RemoveChildAt(i);
				break;
			}
		}
	}
}

void UPackageScrollUserWidget::RemoveSceneItemFromScroll(int32 Site)
{
	for (int32 i = 0; i < ScrollBox->GetChildrenCount(); i++)
	{
		if (UPackageItemUserWidget* Item = Cast<UPackageItemUserWidget>(ScrollBox->GetChildAt(i)))
		{
			if (Item->GetSite() == Site)
			{
				ScrollBox->RemoveChildAt(i);
				break;
			}
		}
	}
}

void UPackageScrollUserWidget::ClearChildren()
{
	ScrollBox->ClearChildren();
}

bool UPackageScrollUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                            UDragDropOperation* InOperation)
{
	if (bIsNearScroll) return false;
	// 从附近过来的
	if (UPackageItemUserWidget* PackageItem = Cast<UPackageItemUserWidget>(InOperation->Payload))
	{
		if (PackageItem->GetSceneItemActor() && bIsNearScroll) return false;
		if (!PackageItem->GetSceneItemActor() && !bIsNearScroll) return false;
		//ScrollBox->AddChild(PackageItem);
		if (ALGPlayerCharacter* MyCharacter = Cast<ALGPlayerCharacter>(GetOwningPlayer()->GetPawn()))
		{
			MyCharacter->GetPackageComponent()->AddItemToPackage(PackageItem->GetSceneItemActor());
		}
		return true;	
	}
	else if (USkinFrameUserWidget* SkinFrameWidget = Cast<USkinFrameUserWidget>(InOperation->Payload))
	{
		//说明在脱掉皮肤
		if (ALGPlayerCharacter* PlayerCharacter = Cast<ALGPlayerCharacter>(GetOwningPlayerPawn()))
		{
			if (PlayerCharacter->GetPackageComponent())
			{
				PlayerCharacter->GetPackageComponent()->TakeoffSkin(SkinFrameWidget->GetSkinType());
			}
		}
		return true;
	}
	else if (UWeaponFrameUserWidget* WeaponFrameWidget = Cast<UWeaponFrameUserWidget>(InOperation->Payload))
	{
		//说明在脱掉枪
		if (ALGPlayerCharacter* PlayerCharacter = Cast<ALGPlayerCharacter>(GetOwningPlayerPawn()))
		{
			if (PlayerCharacter->GetPackageComponent())
			{
				PlayerCharacter->GetPackageComponent()->UnequipWeapon();
			}
		}
	}
	return false;
}
