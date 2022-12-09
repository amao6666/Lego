// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "PackageItemUserWidget.generated.h"


class ASceneItemActor;

/**
 * 
 */
UCLASS()
class LEGOGAME_API UPackageItemUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	void SetItemInfo(ASceneItemActor* ItemActor);
	void SetItemInfo(int32 ID);
	ASceneItemActor* GetSceneItemActor();
	int32 GetSite();
	void SetSite(int32 OutSite);
	
protected:
	int32 Site;
	ASceneItemActor* SceneItemActor;
	UPROPERTY(meta=(BindWidget))
	UImage* ItemImage;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemName;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
};
