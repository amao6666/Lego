// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecorator_CheckLook.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "LegoGame/LegoGame.h"

UBTDecorator_CheckLook::UBTDecorator_CheckLook()
{
	NodeName = TEXT("检查是否可以看到目标");
	BlackboardKey.AddObjectFilter(this, TEXT("BlackboardKey"), AActor::StaticClass());
}

bool UBTDecorator_CheckLook::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (BlackboardKey.IsNone()) return false;
	FVector StartPos = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	FVector EndPos;

	FCollisionQueryParams Parameters;
	Parameters.AddIgnoredActor(OwnerComp.GetAIOwner()->GetPawn());
	
	if (AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID())))
	{
		EndPos = Actor->GetActorLocation();
		Parameters.AddIgnoredActor(Actor);
	}
	else
	{
		return false;
	}

	FHitResult HitResult;

	if (DrawDebugTime > 0)
	{
		DrawDebugLine(OwnerComp.GetAIOwner()->GetWorld(), StartPos + FVector::UpVector * OriginOffset, EndPos + FVector::UpVector * TargetOffset, FColor::Yellow, false, DrawDebugTime);
	}
	
	return OwnerComp.GetAIOwner()->GetWorld()->LineTraceSingleByChannel(HitResult, StartPos + FVector::UpVector * OriginOffset, EndPos + FVector::UpVector * TargetOffset, ECC_WeaponTrace, Parameters);
}
