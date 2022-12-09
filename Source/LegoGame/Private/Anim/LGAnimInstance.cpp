// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/LGAnimInstance.h"
#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"
#include "Weapon/WeaponActor.h"

ULGAnimInstance::ULGAnimInstance(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	WaitRelaxed = 4.f;
}

void ULGAnimInstance::AnimNotify_RelaxedEnd()
{
	bRelaxed = false;
	WaitRelaxed = 4.f;
}

void ULGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!MyCharacter)
	{
		MyCharacter = Cast<ALGCharacterBase>(TryGetPawnOwner());
		return;
	}
	Speed = MyCharacter->GetVelocity().Size2D();
	bIsSprint = MyCharacter->GetIsSprint() && Speed > 0;

	bIsCrouch = MyCharacter->bIsCrouched;
	bHoldWeapon = MyCharacter->IsHoldWeapon();
	bIsAiming = MyCharacter->GetIsAiming();
	
	if (Speed > 0)
	{
		// float CosValue = FVector::DotProduct(MyCharacter->GetVelocity().GetSafeNormal(), MyCharacter->GetActorForwardVector());
		// // 反余弦求弧度,弧度求角度： 弧度 / 角度 = Π / 180
		// Direction = FMath::Acos(CosValue) * 180 / 3.1415f;
		// if (FVector::DotProduct(MyCharacter->GetVelocity().GetSafeNormal(), MyCharacter->GetActorRightVector()) < 0)
		// {
		// 	// 代表速度朝左
		// 	Direction *= -1;
		// }

		Direction = UKismetAnimationLibrary::CalculateDirection(MyCharacter->GetVelocity(), FRotator(0, MyCharacter->GetControlRotation().Yaw, 0));
	}

	if (bHoldWeapon)
	{
		AimPitch = MyCharacter->GetControlRotation().GetNormalized().Pitch;
		HoldWeaponPosition = MyCharacter->GetHoldWeapon()->GetSkeletalMeshComponent()->GetSocketLocation(TEXT("HoldLocation"));
		bIsFire = (MyCharacter->GetHoldWeapon()->GetCurrentState() == EWeaponState::Fire);
	}
	else
	{
		if ((WaitRelaxed -= DeltaSeconds) <= 0)
		{
			bRelaxed = true;
		}
		if (Speed > 0 || bIsFire || bIsAiming || bIsCrouch || bIsSprint)
		{
			bRelaxed = false;
			WaitRelaxed = 4.f;
		}
	}
}
