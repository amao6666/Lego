// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskNode_LockTarget.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UBTTaskNode_LockTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTaskNode_LockTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


protected:

	UPROPERTY(EditAnywhere)
	bool bLockTarget;
};
