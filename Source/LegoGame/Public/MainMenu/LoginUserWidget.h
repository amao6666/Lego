// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta=(Bindwidget))
	class UEditableTextBox* EditableTextAccount;
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* EditableTextPassword;
	UPROPERTY(meta=(BindWidget))
	class UCheckBox* SaveCheckBox;
	UPROPERTY()
	class UAccountSaveGame* AccountSaveGame;
	
	FString SaveGameSlotName;
	
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void LoginAccount();
	
	void SaveAccount();
	void LoadAccount();
};
