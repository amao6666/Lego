// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Subsystem/PropsSubsystem.h"
#include "SkinFrameUserWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class LEGOGAME_API USkinFrameUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	ESkinType SkinType;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SkinSign;
	UPROPERTY(meta=(BindWidget))
	UImage* IconImage;
	
	virtual void NativePreConstruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
public:
	ESkinType GetSkinType(){return SkinType;};
	void UpdateIcon(int32 ID);
};
