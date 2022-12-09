// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Widget/PackageItemUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Scene/SceneItemActor.h"
#include "Subsystem/PropsSubsystem.h"

void UPackageItemUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SceneItemActor = nullptr;
	Site = -1;
}

void UPackageItemUserWidget::SetItemInfo(ASceneItemActor* ItemActor)
{
	if (!ItemActor) return;
	SceneItemActor = ItemActor;
	SetItemInfo(ItemActor->GetID());
}

void UPackageItemUserWidget::SetItemInfo(int32 ID)
{
	UPropsSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UPropsSubsystem>();
	if (const FPropsBase* PropBase = Subsystem->GetPropsByID(ID))
	{
		ItemImage->SetBrushFromTexture(PropBase->Icon);
		ItemName->SetText(PropBase->Name);
	}
}

ASceneItemActor* UPackageItemUserWidget::GetSceneItemActor()
{
	return SceneItemActor;
}

int32 UPackageItemUserWidget::GetSite()
{
	return Site;
}

void UPackageItemUserWidget::SetSite(int32 OutSite)
{
	Site = OutSite;
}

FReply UPackageItemUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UPackageItemUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	// Create Drag Operation
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	// Set Drag Widget, Don't usually use this
	OutOperation->DefaultDragVisual = this;
	// Set Payload
	OutOperation->Payload = this;
	// Set cursor location, Default is EDragPivot::CenterCenter 
	OutOperation->Pivot = EDragPivot::MouseDown;
}
