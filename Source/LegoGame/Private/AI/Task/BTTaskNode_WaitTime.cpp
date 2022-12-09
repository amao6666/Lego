// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTaskNode_WaitTime.h"

UBTTaskNode_WaitTime::UBTTaskNode_WaitTime()
{
	NodeName = TEXT("等待时间");
	WaitTime = 5.f;
	RandomDeviation = 0;
	bNotifyTick = true;
	// 所有人使用该节点时都会使用新的实例
	//bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTaskNode_WaitTime::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (RandomDeviation > 0)
	{
		// 使用独立空间存储CurrentTime
		*(float*)NodeMemory = FMath::FRandRange(WaitTime - RandomDeviation, WaitTime + RandomDeviation);
	}
	else
	{
		*(float*)NodeMemory = WaitTime;
	}
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_WaitTime::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if ((*(float*)NodeMemory -= DeltaSeconds) <= 0)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

uint16 UBTTaskNode_WaitTime::GetInstanceMemorySize() const
{
	// 每个节点实例开辟单独的控件
	return sizeof(float);
}
