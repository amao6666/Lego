// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CheckLook.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UBTDecorator_CheckLook : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckLook();
	
protected:
	UPROPERTY(EditAnywhere)
	float TargetOffset;
	UPROPERTY(EditAnywhere)
	float OriginOffset;
	UPROPERTY(EditAnywhere)
	float DrawDebugTime;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
