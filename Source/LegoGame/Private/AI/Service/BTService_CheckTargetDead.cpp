// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_CheckTargetDead.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Character/LGCharacterBase.h"

UBTService_CheckTargetDead::UBTService_CheckTargetDead()
{
	NodeName = TEXT("检查目标是否死亡");
	BlackboardKey.AddObjectFilter(this, TEXT("BlackboardKey"), ALGCharacterBase::StaticClass());
}

void UBTService_CheckTargetDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (TargetKey.IsNone() || BlackboardKey.IsNone())
	{
		return;
	}

	if (ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID())))
	{
		if (CharacterBase->GetIsDead())
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(TargetKey.GetSelectedKeyID());
		}
	}
}

void UBTService_CheckTargetDead::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBData = GetBlackboardAsset();

	if (BBData)
	{
		TargetKey.ResolveSelectedKey(*BBData);
	}
}
