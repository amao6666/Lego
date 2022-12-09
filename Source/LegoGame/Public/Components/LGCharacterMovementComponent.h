// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LGCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API ULGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	ULGCharacterMovementComponent();

protected:
	UPROPERTY(Category="Character Movement: Walking", EditAnywhere, BlueprintReadWrite)
	float SprintSpeed;

	virtual float GetMaxSpeed() const override;
};
