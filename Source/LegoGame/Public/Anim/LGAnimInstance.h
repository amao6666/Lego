// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player/LGPlayerCharacter.h"
#include "LGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API ULGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	ULGAnimInstance(const FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION()
	void AnimNotify_RelaxedEnd();
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsSprint:1;
	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	uint8 bIsCrouch:1;
	UPROPERTY(BlueprintReadOnly)
	uint8 bHoldWeapon : 1;
	UPROPERTY(BlueprintReadOnly)
	uint8 bIsAiming : 1;
	UPROPERTY(BlueprintReadOnly)
	float Direction;
	UPROPERTY(BlueprintReadOnly)
	float AimPitch;
	UPROPERTY(BlueprintReadOnly)
	FVector HoldWeaponPosition;
	UPROPERTY(BlueprintReadOnly)
	uint8 bIsFire : 1;
	UPROPERTY(BlueprintReadOnly)
	uint8 bRelaxed : 1;
	UPROPERTY()
	ALGCharacterBase* MyCharacter;

	float WaitRelaxed;
};
