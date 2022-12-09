// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTaskNode_FindNavPoint.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


UBTTaskNode_FindNavPoint::UBTTaskNode_FindNavPoint()
{
	NodeName = TEXT("寻找导航点");
	//设置黑板键值拾取器对于类型得约束
	TargetPosKey.AddVectorFilter(this, TEXT("TargetPosKey"));

	OriginPosKey.AddVectorFilter(this, TEXT("OriginPosKey"));
	OriginPosKey.AddObjectFilter(this, TEXT("OriginPosKey"), AActor::StaticClass());

	NavRadius = 1000;
}

EBTNodeResult::Type UBTTaskNode_FindNavPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//检查键值有效性
	if (OriginPosKey.IsNone() || TargetPosKey.IsNone())
	{
		return EBTNodeResult::Failed;
	}
	FVector OriginPos;
	FVector TargetPos;
	//检查键值拾取类型得方法
	if (OriginPosKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		OriginPos = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(OriginPosKey.GetSelectedKeyID());
	}
	else
	{
		if (AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(OriginPosKey.GetSelectedKeyID())))
		{
			OriginPos = Actor->GetActorLocation();
		}
	}

	//TargetPos = OriginPos + FRotator(0, FMath::RandRange(0, 360), 0).Vector() * FMath::RandRange(500, 1000);
	//OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(TargetPosKey.GetSelectedKeyID(), TargetPos);

	if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(OwnerComp.GetAIOwner(), OriginPos, TargetPos, NavRadius))
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(TargetPosKey.GetSelectedKeyID(), TargetPos);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UBTTaskNode_FindNavPoint::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBData = GetBlackboardAsset();
	if (BBData)
	{
		TargetPosKey.ResolveSelectedKey(*BBData);
		OriginPosKey.ResolveSelectedKey(*BBData);
	}
}
