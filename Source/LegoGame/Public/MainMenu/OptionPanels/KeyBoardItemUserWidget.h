// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyBoardItemUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UKeyBoardItemUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ChangeKeyBoardInfo(FText BoardName, FKey Key, FName OutKeyEventName, float OutKeyScale);
	void SetInputKey(FKey NewKey);
	void SetKeySelector(FKey NewKey);
	
	FName GetKeyEventName(){return KeyEventName;};
	float GetKeyScale(){return KeyScale;};
	FKey GetCurrentKey(){return CurrentKey;};

protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnKeySelected(FInputChord SelectedKey);

protected:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* KeyStringTextBlock;
	UPROPERTY(meta=(BindWidget))
	class UInputKeySelector* KeySelector;

	FKey CurrentKey;

	FName KeyEventName;
	float KeyScale;
};
