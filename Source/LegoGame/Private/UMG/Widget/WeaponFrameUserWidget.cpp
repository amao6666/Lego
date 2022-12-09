// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Widget/WeaponFrameUserWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Character/LGCharacterBase.h"
#include "Components/PackageActorComponent.h"
#include "UMG/PackageUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UMG/Widget/PackageItemUserWidget.h"


void UWeaponFrameUserWidget::UpdateIcon(int32 ID)
{
	if (ID == -1)
	{
		IconImage->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		IconImage->SetVisibility(ESlateVisibility::Visible);

		const FPropsBase* PropsBase = GetOwningPlayer()->GetWorld()->GetGameInstance()->GetSubsystem<UPropsSubsystem>()->GetPropsByID(ID);
		if (PropsBase)
		{
			IconImage->SetBrushFromTexture(PropsBase->Icon);
		}
	}
}

bool UWeaponFrameUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                          UDragDropOperation* InOperation)
{
	if (UPackageItemUserWidget* BoardWidget = Cast<UPackageItemUserWidget>(InOperation->Payload))
	{
		if (ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(GetOwningPlayerPawn()))
		{
			if (BoardWidget->GetSceneItemActor()) //附近过来的穿戴
			{
				CharacterBase->GetPackageComponent()->EquipWeapon(BoardWidget->GetSceneItemActor());
			}
			else //背包过来的穿戴
			{
				CharacterBase->GetPackageComponent()->EquipWeapon(BoardWidget->GetSite());
			}
			return true;
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

FReply UWeaponFrameUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this, EKeys::LeftMouseButton).NativeReply;
}

void UWeaponFrameUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	OutOperation->Payload= this;
	OutOperation->DefaultDragVisual = this;
	OutOperation->Pivot = EDragPivot::MouseDown;
}
