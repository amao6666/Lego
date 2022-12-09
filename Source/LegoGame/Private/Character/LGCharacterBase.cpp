// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LGCharacterBase.h"
#include "Components/LGCharacterMovementComponent.h"
#include "Components/PackageActorComponent.h"
#include "Components/SkinActorComponent.h"
#include "Weapon/WeaponActor.h"

// Sets default values
ALGCharacterBase::ALGCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<ULGCharacterMovementComponent>(CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PackageComponent = CreateDefaultSubobject<UPackageActorComponent>(TEXT("PackageComp"));

	SkinComponent = CreateDefaultSubobject<USkinActorComponent>(TEXT("SkinComp"));
}

// Called when the game starts or when spawned
void ALGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	PackageComponent->OnSkinPuton.AddUObject(SkinComponent, &USkinActorComponent::OnSkinPuton);
	PackageComponent->OnSkinTakeoff.AddUObject(SkinComponent, &USkinActorComponent::OnSkinTakeoff);
}

// Called every frame
void ALGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

USkeletalMeshComponent* ALGCharacterBase::GetSkinSkeletalMeshComponent()
{
	return GetMesh();
}

void ALGCharacterBase::DoCrouch()
{
	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void ALGCharacterBase::DoJump()
{
	Jump();
}

void ALGCharacterBase::StartSprint()
{
	if (bIsFire) EndFire();
	if (bIsCrouched) return;
	bIsSprint = true;
}

void ALGCharacterBase::EndSprint()
{
	bIsSprint = false;
}

void ALGCharacterBase::StartAim()
{
	if (!IsHoldWeapon()) return;
	bIsAiming = true;
}

void ALGCharacterBase::EndAim()
{
	bIsAiming = false;
}

void ALGCharacterBase::StartFire()
{
	if (!IsHoldWeapon() || GetIsSprint()) return;
	bIsFire = true;
	GetHoldWeapon()->StartFire();
}

void ALGCharacterBase::EndFire()
{
	if (!IsHoldWeapon()) return;
	bIsFire = false;
	GetHoldWeapon()->EndFire();
}

void ALGCharacterBase::DoReload()
{
	if (!IsHoldWeapon()) return;
	GetHoldWeapon()->ReloadBullets();
}

float ALGCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                   AActor* DamageCauser)
{
	if (OnDamaged.IsBound())
	{
		OnDamaged.Broadcast(Cast<ALGCharacterBase>(EventInstigator->GetPawn()));
	}
	return 0;
}

bool ALGCharacterBase::GetIsSprint()
{
	if (IsHoldWeapon())
	{
		return bIsSprint && !bIsCrouched && FVector::DotProduct(GetVelocity().GetSafeNormal(), GetActorForwardVector()) > 0.9f;
	}
	else
	{
		return bIsSprint && !bIsCrouched;
	}
}

bool ALGCharacterBase::GetIsAiming()
{
	return bIsAiming;
}

bool ALGCharacterBase::IsHoldWeapon()
{
	return PackageComponent && PackageComponent->GetHoldWeapon();
}

void ALGCharacterBase::SetBlockView(bool bIsBlockView)
{
	bUseControllerRotationYaw = bIsBlockView;
	GetCharacterMovement()->bOrientRotationToMovement = !bIsBlockView;
}

AWeaponActor* ALGCharacterBase::GetHoldWeapon()
{
	return GetPackageComponent()->GetHoldWeapon();
}

UPackageActorComponent* ALGCharacterBase::GetPackageComponent()
{
	return PackageComponent;
}

USkinActorComponent* ALGCharacterBase::GetSkinComponent()
{
	return SkinComponent;
}

