// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMainMenuUserWidget;
class URoomListUserWidget;
class UWaitingUserWidget;

/**
 * 
 */
UCLASS()
class LEGOGAME_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
public:
	AMainMenuHUD();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetMainMenuShow(bool bIsShow);
	UFUNCTION(BlueprintCallable)
	void SetRoomListShow(bool bIsShow);

	UFUNCTION(BlueprintCallable)
	void SetWaitingShow(bool bIsShow, bool bIsAutoClose = false, int32 WaitSeconds = 5);
	
protected:
	UMainMenuUserWidget* MainMenuUI;
	URoomListUserWidget* RoomListUI;
	UWaitingUserWidget* WaitingUI;
};
