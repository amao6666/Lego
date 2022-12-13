// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTaskNode_ClearValueByKey.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_ClearValueByKey::UBTTaskNode_ClearValueByKey()
{
	NodeName = TEXT("清除黑板键值");
}

EBTNodeResult::Type UBTTaskNode_ClearValueByKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (BlackboardKey.IsNone())
	{
		return EBTNodeResult::Failed;
	}
	OwnerComp.GetBlackboardComponent()->ClearValue(BlackboardKey.GetSelectedKeyID());
	return EBTNodeResult::Succeeded;
}
