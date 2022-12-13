// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LGCharacterBase.h"

#include "Components/BillboardComponent.h"
#include "Components/LGCharacterMovementComponent.h"
#include "Components/PackageActorComponent.h"
#include "Components/SkinActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapon/WeaponActor.h"
#include "LegoGame/LegoGame.h"

// Sets default values
ALGCharacterBase::ALGCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<ULGCharacterMovementComponent>(CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PackageComponent = CreateDefaultSubobject<UPackageActorComponent>(TEXT("PackageComp"));

	SkinComponent = CreateDefaultSubobject<USkinActorComponent>(TEXT("SkinComp"));
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComp"));
	BillboardComponent->SetupAttachment(RootComponent);
	BillboardComponent->SetRelativeLocation(FVector(0, 0, 160));
	MaxHP = 100;
}

void ALGCharacterBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	// if (IGenericTeamAgentInterface* TeamInterface = Cast<IGenericTeamAgentInterface>(GetController()))
	// {
	// 	//根据自己当前的阵营标记，更改广告牌的内容
	// 	if (BillboardComponent)
	// 	{
	// 		TCHAR* Path = TEXT("Texture2D'/Game/Lego/Textures/MapIcons/1.1'");
	// 		FGenericTeamId TeamId = TeamInterface->GetGenericTeamId();
	// 		
	// 		if (TeamId.GetId() == 1)
	// 		{
	// 			Path = TEXT("Texture2D'/Game/Lego/Textures/MapIcons/2.2'");
	// 		}
	// 		else if (TeamId.GetId() == 2)
	// 		{
	// 			Path = TEXT("Texture2D'/Game/Lego/Textures/MapIcons/3.3'");
	// 		}
	// 	
	// 		UTexture2D* Icon = LoadObject<UTexture2D>(this, Path);
	// 		BillboardComponent->SetSprite(Icon);
	// 	}
	// }
	//根据自己当前的阵营标记，更改广告牌的内容
	if (BillboardComponent)
	{
		TCHAR* Path = TEXT("Texture2D'/Game/Lego/Textures/MapIcons/1.1'");
		FGenericTeamId TeamId = GetGenericTeamId();
			
		if (TeamId.GetId() == 1)
		{
			Path = TEXT("Texture2D'/Game/Lego/Textures/MapIcons/2.2'");
		}
		else if (TeamId.GetId() == 2)
		{
			Path = TEXT("Texture2D'/Game/Lego/Textures/MapIcons/3.3'");
		}
		UTexture2D* Icon = LoadObject<UTexture2D>(this, Path);
		BillboardComponent->SetSprite(Icon);
	}
}

// Called when the game starts or when spawned
void ALGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	PackageComponent->OnSkinPuton.AddUObject(SkinComponent, &USkinActorComponent::OnSkinPuton);
	PackageComponent->OnSkinTakeoff.AddUObject(SkinComponent, &USkinActorComponent::OnSkinTakeoff);
	HP = MaxHP;
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

FGenericTeamId ALGCharacterBase::GetGenericTeamId() const
{
	// if (IGenericTeamAgentInterface* TeamInterface = Cast<IGenericTeamAgentInterface>(GetController()))
	// {
	// 	return TeamInterface->GetGenericTeamId();
	// }
	// return FGenericTeamId::NoTeam;
	if (TeamColor == ETeamColor::ETC_Blue)
	{
		return TeamID_Blue;
	}
	else if (TeamColor == ETeamColor::ETC_Yellow)
	{
		return TeamID_Yellow;
	}
	return TeamID_Red;
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
	if (HP <= 0)
	{
		return 0;
	}

	HP--;

	if (HP <= 0)
	{
		//解除控制
		GetController()->UnPossess();
		//布娃娃模拟
		GetMesh()->SetSimulatePhysics(true);
		//添加冲力
		const FPointDamageEvent* PointDamageEvent = static_cast<const FPointDamageEvent*>(&DamageEvent);
		//枪械到击中点
		FVector ForceDir = (PointDamageEvent->HitInfo.Location - DamageCauser->GetActorLocation()).GetSafeNormal();

		GetMesh()->AddImpulse(ForceDir * 2000, PointDamageEvent->HitInfo.BoneName, true);

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
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

ETeamColor ALGCharacterBase::GetTeamColor() const
{
	return TeamColor;
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

