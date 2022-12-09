// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/LGPlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/LGPlayerCharacter.h"
#include "Camera/CameraComponent.h"

void ALGPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	// Change ArmSpring location
	if (ALGPlayerCharacter* MyCharacter = Cast<ALGPlayerCharacter>(GetOwningPlayerController()->GetPawn()))
	{
		if (MyCharacter->bIsCrouched && !bCrouched)
		{
			SpringArmZ = 44;
		}
		else if (!MyCharacter->bIsCrouched && bCrouched)
		{
			SpringArmZ = -44;
		}
		bCrouched = MyCharacter->bIsCrouched;
		SpringArmZ = FMath::FInterpTo(SpringArmZ, 0, DeltaTime, 10);
		MyCharacter->GetSpringArmComponent()->SetRelativeLocation(FVector(0, 0, SpringArmZ));

		
		//调整持枪spring动画
		float CameraRelX = MyCharacter->GetCameraComponent()->GetRelativeLocation().X;
		float SprintSocketY = MyCharacter->GetSpringArmComponent()->SocketOffset.Y;
		float SpringTargetZ = MyCharacter->GetSpringArmComponent()->TargetOffset.Z;

		if (MyCharacter->IsHoldWeapon())
		{
			CameraRelX = FMath::FInterpTo(CameraRelX, 150, DeltaTime, 10);
			SpringTargetZ = FMath::FInterpTo(SpringTargetZ, 50, DeltaTime, 10);
			SprintSocketY = FMath::FInterpTo(SprintSocketY, 80, DeltaTime, 10);
		}
		else
		{
			CameraRelX = FMath::FInterpTo(CameraRelX, 0, DeltaTime, 10);
			SpringTargetZ = FMath::FInterpTo(SpringTargetZ, 0, DeltaTime, 10);
			SprintSocketY = FMath::FInterpTo(SprintSocketY, 0, DeltaTime, 10);
		}
		
		MyCharacter->GetCameraComponent()->SetRelativeLocation(FVector(CameraRelX, 0, 0));
		MyCharacter->GetSpringArmComponent()->SocketOffset.Y = SprintSocketY;
		MyCharacter->GetSpringArmComponent()->TargetOffset.Z = SpringTargetZ;

		// 瞄准时调整相机焦距
		DefaultFOV = FMath::FInterpTo(DefaultFOV, MyCharacter->GetIsAiming() ? 60 : 90, DeltaTime, 10);
		SetFOV(DefaultFOV);
	}
	Super::UpdateCamera(DeltaTime);
}
