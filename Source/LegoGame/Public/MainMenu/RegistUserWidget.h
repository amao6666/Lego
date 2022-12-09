// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "RegistUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API URegistUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(meta=(BindWidget))
	UButton* SendCodeButton;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SendCodeButtonText;
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* EditableTextEmail;
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* EditableTextAccount;
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* EditableTextPassword;
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* EditableTextValidCode;
	
	UPROPERTY()
	int32 SendCodeSecond;

	FTimerHandle TimerHandle;
	
	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void OnSendCodeButtonClicked();

	void SendCodeTimerCallback();

	void RestSendCodeButton();

	bool ValidationEmail();
};
