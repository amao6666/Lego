// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LGCharacterMovementComponent.h"

#include "Character/LGCharacterBase.h"

ULGCharacterMovementComponent::ULGCharacterMovementComponent()
{
	SprintSpeed = 1500;
}

float ULGCharacterMovementComponent::GetMaxSpeed() const
{
	float Speed = Super::GetMaxSpeed();
	if (ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(GetOwner()))
	{
		if (CharacterBase->GetIsSprint())
		{
			Speed = SprintSpeed;
		}
	}
	return Speed;
}
