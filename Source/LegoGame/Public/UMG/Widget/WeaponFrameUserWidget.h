// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "WeaponFrameUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UWeaponFrameUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void UpdateIcon(int32 ID);
	
protected:
	UPROPERTY(meta=(BindWidget))
	UImage* IconImage;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
};
