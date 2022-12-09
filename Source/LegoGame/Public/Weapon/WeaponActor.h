// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "WeaponActor.generated.h"

UENUM()
enum class EWeaponState : uint8
{
	Normal,
	Fire,
	Reload,
	Empty
};

class ALGCharacterBase;

UCLASS()
class LEGOGAME_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnBullet();
	void SpawnEffect();
	void SpawnDamage();
	void GetFirePositionAndDirection(FVector& Position, FVector& Direction);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetMaster(ALGCharacterBase* CharacterBase);
	void SetID(int32 OutID){ID = OutID;}
	int32 GetID(){return ID;}
	USkeletalMeshComponent* GetSkeletalMeshComponent();
	void StartFire();
	void EndFire();
	void SetMaxBulletNumber(int32 Number);
	int32 GetMaxBulletNumber();
	int32 GetCurrentBulletNumber();
	void ReloadBullets();
	void FinishReload();
	EWeaponState GetCurrentState();

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;
	int32 ID;
	UPROPERTY(EditAnywhere)
	int32 MaxBulletNumber;
	UPROPERTY()
	int32 CurrentBulletNumber;
	UPROPERTY(EditAnywhere)
	float FireInterval;
	UPROPERTY(EditAnywhere)
	USoundCue* FireSound;
	UPROPERTY(EditAnywhere)
	UParticleSystem* FireParticle;
	UPROPERTY(EditAnywhere)
	UAnimMontage* ReloadMontage;

	FTimerHandle FireTimerHandle;

	float LastToggleTime;
	ALGCharacterBase* MyMaster;

	EWeaponState CurrentState;
};
