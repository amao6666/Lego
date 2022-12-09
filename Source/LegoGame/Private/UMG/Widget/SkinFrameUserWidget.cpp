// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Widget/SkinFrameUserWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Character/LGCharacterBase.h"
#include "Components/PackageActorComponent.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UMG/Widget/PackageItemUserWidget.h"

void USkinFrameUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (SkinSign)
	{
		FText SignText;
		if (SkinType == ESkinType::EST_Bag)
		{
			SignText = NSLOCTEXT("frameWiget", "k1", "包");
		}
		else if (SkinType == ESkinType::EST_Beard)
		{
			SignText = NSLOCTEXT("frameWiget", "k2", "胡");
		}
		else if (SkinType == ESkinType::EST_Coat)
		{
			SignText = NSLOCTEXT("frameWiget", "k3", "衣");
		}
		else if (SkinType == ESkinType::EST_Eyeshades)
		{
			SignText = NSLOCTEXT("frameWiget", "k4", "罩");
		}
		else if (SkinType == ESkinType::EST_Facemask)
		{
			SignText = NSLOCTEXT("frameWiget", "k5", "面");
		}
		else if (SkinType == ESkinType::EST_Hair)
		{
			SignText = NSLOCTEXT("frameWiget", "k6", "发");
		}
		else if (SkinType == ESkinType::EST_Glasses)
		{
			SignText = NSLOCTEXT("frameWiget", "k7", "镜");
		}
		else if (SkinType == ESkinType::EST_Helmet)
		{
			SignText = NSLOCTEXT("frameWiget", "k8", "盔");
		}
		else
		{
			SignText = NSLOCTEXT("frameWiget", "k12", "未");
		}
		
		SkinSign->SetText(SignText);
	}
}

bool USkinFrameUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (UPackageItemUserWidget* BoardWidget = Cast<UPackageItemUserWidget>(InOperation->Payload))
	{
		if (ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(GetOwningPlayerPawn()))
		{
			if (BoardWidget->GetSceneItemActor())
			{
				//从附近直接拖拽过来
				CharacterBase->GetPackageComponent()->PutonSkin(BoardWidget->GetSceneItemActor(), SkinType);
			}
			else
			{
				//从背包拖拽过来
				CharacterBase->GetPackageComponent()->PutonSkin(BoardWidget->GetSite(), SkinType);
			}
			return true;
		}
	}
	return false;
}

FReply USkinFrameUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (IconImage->IsVisible())
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	else
	{
		return FReply::Unhandled();
	}
}

void USkinFrameUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                                UDragDropOperation*& OutOperation)
{
	// Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	OutOperation->Payload = this;
	OutOperation->DefaultDragVisual = this;
	OutOperation->Pivot = EDragPivot::MouseDown;
}

void USkinFrameUserWidget::UpdateIcon(int32 ID)
{
	if (ID == -1)
	{
		IconImage->SetVisibility(ESlateVisibility::Hidden);
		SkinSign->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		IconImage->SetVisibility(ESlateVisibility::Visible);
		SkinSign->SetVisibility(ESlateVisibility::Hidden);

		const FPropsBase* PropsBase = GetOwningPlayer()->GetWorld()->GetGameInstance()->GetSubsystem<UPropsSubsystem>()->GetPropsByID(ID);
		if (PropsBase)
		{
			IconImage->SetBrushFromTexture(PropsBase->Icon);
		}
	}
}
