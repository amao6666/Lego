// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "KeyMapUserWidget.generated.h"

USTRUCT()
struct FWidgetKeyInfo : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FName KeyEventName;
	UPROPERTY(EditAnywhere)
	FText KeyEventDescription;
	UPROPERTY(EditAnywhere)
	FKey Key;
	UPROPERTY(EditAnywhere)
	float Scale;
};

/**
 * 
 */
UCLASS()
class LEGOGAME_API UKeyMapUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void ResetAllKey();

protected:
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* KeysVerticalBox;
	UPROPERTY()
	UDataTable* KeyInfoDT;
};
