// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UFUNCTION(BlueprintCallable)
	void ShowGameSettingPanel();

	UFUNCTION(BlueprintCallable)
	void ShowLoginPanel();

protected:
	class UOptionUserWidget* OptionUI;
	class ULoginUserWidget* LoginUI;
};
