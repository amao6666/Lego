// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskNode_ClearValueByKey.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UBTTaskNode_ClearValueByKey : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTaskNode_ClearValueByKey();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
