// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "PackageScrollUserWidget.generated.h"

class ASceneItemActor;

/**
 * 
 */
UCLASS()
class LEGOGAME_API UPackageScrollUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddSceneItemToScroll(ASceneItemActor* ItemActor);
	void AddSceneItemToScroll(int32 Site, int32 ID);
	void RemoveSceneItemFromScroll(ASceneItemActor* ItemActor);
	void RemoveSceneItemFromScroll(int32 Site);
	void ClearChildren();
	
protected:
	UPROPERTY(meta=(BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(EditAnywhere)
	uint8 bIsNearScroll : 1;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
