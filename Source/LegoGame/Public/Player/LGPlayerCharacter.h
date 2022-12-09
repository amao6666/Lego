// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LGCharacterBase.h"
#include "LGPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class LEGOGAME_API ALGPlayerCharacter : public ALGCharacterBase
{
	GENERATED_BODY()
public:
	ALGPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	USpringArmComponent* GetSpringArmComponent();
	UCameraComponent* GetCameraComponent();
	
protected:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent; 
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* ArmComponent;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* MainCamera;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void TurnRate(float Value);

	void TogglePackage();
	UFUNCTION()
	void OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnSphereComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
