// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_WaitTime.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UBTTaskNode_WaitTime : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_WaitTime();

protected:
	UPROPERTY(EditAnywhere)
	float WaitTime;
	UPROPERTY(EditAnywhere)
	float RandomDeviation;

	float CurrentTime;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual uint16 GetInstanceMemorySize() const override;
};
