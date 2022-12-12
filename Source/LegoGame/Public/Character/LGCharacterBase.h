// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Interface/SkinInterface.h"
#include "LGCharacterBase.generated.h"

UENUM()
enum class ETeamColor
{
	ETC_Red,
	ETC_Blue,
	ETC_Yellow
};

class AWeaponActor;
class ALGCharacterBase;

DECLARE_MULTICAST_DELEGATE_OneParam(NotifyDamage, ALGCharacterBase*);

UCLASS()
class LEGOGAME_API ALGCharacterBase : public ACharacter, public ISkinInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALGCharacterBase(const FObjectInitializer& ObjectInitializer);
	NotifyDamage OnDamaged;

protected:
	bool bIsSprint;
	bool bIsAiming;
	bool bIsFire;
	UPROPERTY(VisibleAnywhere)
	UBillboardComponent* BillboardComponent;
	UPROPERTY(EditAnywhere)
	ETeamColor TeamColor;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(VisibleAnywhere)
	class UPackageActorComponent* PackageComponent;
	UPROPERTY()
	class USkinActorComponent* SkinComponent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual USkeletalMeshComponent* GetSkinSkeletalMeshComponent() override;

	virtual FGenericTeamId GetGenericTeamId() const override;

	void DoCrouch();

	void DoJump();
	void StartSprint();
	void EndSprint();
	
	void StartAim();
	void EndAim();

	void StartFire();
	void EndFire();

	void DoReload();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
public:
	bool GetIsSprint();
	bool GetIsAiming();
	bool IsHoldWeapon();
	void SetBlockView(bool bIsBlockView);
	ETeamColor GetTeamColor() const;
	AWeaponActor* GetHoldWeapon(); 
	UPackageActorComponent* GetPackageComponent();
	USkinActorComponent* GetSkinComponent();
};
