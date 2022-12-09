// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SearchNearby.generated.h"

class AWeaponActor;
class ALGCharacterBase;

/**
 * 
 */
UCLASS()
class LEGOGAME_API UBTService_SearchNearby : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SearchNearby();

protected:
	UPROPERTY(EditAnywhere)
	float SearchRadius;
	UPROPERTY()
	ALGCharacterBase* MyCharacterBase;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
	void OnEquipWeapon(AWeaponActor* WeaponActor);
	void OnDamaged(ALGCharacterBase* HitCharacter);
};
