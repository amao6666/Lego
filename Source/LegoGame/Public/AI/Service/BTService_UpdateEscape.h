// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateEscape.generated.h"

class ALGCharacterBase;

/**
 * 
 */
UCLASS()
class LEGOGAME_API UBTService_UpdateEscape : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdateEscape();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
	void OnDamaged(ALGCharacterBase* HitCharacter);

protected:
	UPROPERTY(EditAnywhere)
	float EscapeTime;

	float CalmTime;
};
