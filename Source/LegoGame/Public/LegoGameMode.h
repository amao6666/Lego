// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LegoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API ALegoGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ALegoGameMode();

protected:
	virtual void BeginPlay() override;
};
