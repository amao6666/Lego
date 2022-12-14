// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckTargetDead.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UBTService_CheckTargetDead : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:

	UBTService_CheckTargetDead();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetKey;
};
