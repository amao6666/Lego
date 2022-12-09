// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LegoGameHUD.generated.h"

class UPackageUserWidget;

/**
 * 
 */
UCLASS()
class LEGOGAME_API ALegoGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	ALegoGameHUD();

	virtual void BeginPlay() override;

	void TogglePackageShow();

	virtual void DrawHUD() override;
	
protected:
	UPROPERTY()
	UPackageUserWidget* PackageUI;
};
