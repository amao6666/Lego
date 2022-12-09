// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "WaitingUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UWaitingUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WaitingTextBlock;

	FTimerHandle TimerHandle;
	UPROPERTY()
	int32 RemainSeconds;
public:
	void AutoClose(int WaitSeconds);
	void ChangeWaitingText();
	
	UFUNCTION()
	void TimerCallback();
};
