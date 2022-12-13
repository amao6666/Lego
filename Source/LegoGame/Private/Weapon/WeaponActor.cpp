// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponActor.h"
#include "Character/LGCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "LegoGame/LegoGame.h"
#include "Player/LGPlayerCharacter.h"
#include "Player/LGPlayerController.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SetRootComponent(SkeletalMeshComponent);
	CurrentState = EWeaponState::Normal;
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	CurrentBulletNumber = MaxBulletNumber;	
}

void AWeaponActor::SpawnBullet()
{
	if (CurrentBulletNumber <= 0) return;
	//生成效果
	SpawnEffect();
	//生成伤害
	SpawnDamage();
	LastToggleTime = GetWorld()->GetTimeSeconds();
	if ((--CurrentBulletNumber) > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AWeaponActor::SpawnBullet, FireInterval);
	}
	else
	{
		CurrentState = EWeaponState::Empty;
	}
}

void AWeaponActor::SpawnEffect()
{
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	}
	if (FireParticle)
	{
		//FVector MuzzlePos = SkeletalMeshComponent->GetSocketLocation(TEXT("Muzzle"));
		//FRotator MuzzleRot = SkeletalMeshComponent->GetSocketRotation(TEXT("Muzzle"));
		UGameplayStatics::SpawnEmitterAttached(FireParticle, SkeletalMeshComponent, TEXT("Muzzle"));
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticle, MuzzlePos, MuzzleRot);
	}
}

void AWeaponActor::SpawnDamage()
{
	FVector Position;
	FVector Direction;
	GetFirePositionAndDirection(Position, Direction);

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Position, Position + Direction * 50000, ECC_WeaponTrace))
	{
		DrawDebugLine(GetWorld(), Position, HitResult.Location, FColor::Green, false, 3, 0, 2);
		//让撞击到目标受伤
		if (IsValid(HitResult.GetActor()))
		{
			FPointDamageEvent Event;
			Event.HitInfo = HitResult;
			HitResult.GetActor()->TakeDamage(1, Event, MyMaster->GetController(), this);
		}
	}
	// 发射射线
	DrawDebugLine(GetWorld(), Position, Position + Direction * 50000, FColor::Red, false, 3);
}

void AWeaponActor::GetFirePositionAndDirection(FVector& Position, FVector& Direction)
{
	if (MyMaster)
	{
		Position = GetSkeletalMeshComponent()->GetSocketLocation(TEXT("Muzzle"));
		Direction = GetSkeletalMeshComponent()->GetSocketRotation(TEXT("Muzzle")).Vector();
		// 玩家是从屏幕中心到场景中发射射线
		if (Cast<ALGPlayerCharacter>(MyMaster))
		{
			if (ALGPlayerController* PC = Cast<ALGPlayerController>(MyMaster->GetController()))
			{
				// 获取屏幕大小
				int32 ScreenX, ScreenY;
				PC->GetViewportSize(ScreenX, ScreenY);
				// 获取屏幕中心在世界坐标的位置
				FVector WorldPosition;
				FVector WorldDirection;
				if (PC->DeprojectScreenPositionToWorld(ScreenX / 2, ScreenY / 2, WorldPosition, WorldDirection))
				{
					// 相当于相机位置像屏幕中心发射一条射线
					DrawDebugLine(GetWorld(), WorldPosition, WorldPosition + WorldDirection * 50000, FColor::Green, false, 3);
					// 发射检测
					FHitResult HitResult;
					if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldPosition, WorldPosition + WorldDirection * 50000, ECC_WeaponTrace))
					{
						if (IsValid(HitResult.GetActor()))
						{
							Direction = (HitResult.Location - Position).GetSafeNormal();
						}
					}
				}
				
			}
		}
		else
		{
			// 如过是Enemy
			Direction = MyMaster->GetControlRotation().Vector();

			FHitResult Hit;

			//设置忽略目标
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(MyMaster);
		
			if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() + Direction * 50000, ECC_WeaponTrace, Params))
			{
				// // Direction = (Hit.Location - Position);
				// //UE_LOG(LogTemp, Log, TEXT("=== %s"), *Hit.Actor->GetName());
				// if (Hit.Actor.IsValid())
				// {
				// 	UE_LOG(LogTemp, Log, TEXT("=== %s"), *Hit.Actor->GetName());
				// }
				// DrawDebugLine(GetWorld(), Position, Hit.Location, FColor::Green, false, 5);
				Direction = (Hit.Location - Position).GetSafeNormal();
			}
		}
	}
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::SetMaster(ALGCharacterBase* CharacterBase)
{
	//将枪械依附在角色手上
	SkeletalMeshComponent->AttachToComponent(CharacterBase->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
	MyMaster = CharacterBase;
}

USkeletalMeshComponent* AWeaponActor::GetSkeletalMeshComponent()
{
	return SkeletalMeshComponent;
}

void AWeaponActor::StartFire()
{
	// 限制连续点击鼠标触发开火
	if (CurrentState != EWeaponState::Normal) return;
	CurrentState = EWeaponState::Fire;
	if (GetWorld()->GetTimeSeconds() - LastToggleTime <= FireInterval) return;
	SpawnBullet();
}

void AWeaponActor::EndFire()
{
	if (CurrentState == EWeaponState::Reload) return;
	if (CurrentState != EWeaponState::Empty)
	{
		CurrentState = EWeaponState::Normal;
	}
	if (FireTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	}
}

void AWeaponActor::SetMaxBulletNumber(int32 Number)
{
	MaxBulletNumber = Number;
}

int32 AWeaponActor::GetMaxBulletNumber()
{
	return MaxBulletNumber;
}

int32 AWeaponActor::GetCurrentBulletNumber()
{
	return CurrentBulletNumber;
}

float AWeaponActor::ReloadBullets()
{
	if (CurrentState == EWeaponState::Reload) return 0.f;
	if (CurrentState == EWeaponState::Fire)
	{
		EndFire();
	}
	CurrentState = EWeaponState::Reload;
	if (ReloadMontage && MyMaster)
	{
	 return	MyMaster->PlayAnimMontage(ReloadMontage);
	}
	return 0.f;
}

void AWeaponActor::FinishReload()
{
	CurrentBulletNumber = MaxBulletNumber;
	CurrentState = EWeaponState::Normal;
}

EWeaponState AWeaponActor::GetCurrentState()
{
	return CurrentState;
}

