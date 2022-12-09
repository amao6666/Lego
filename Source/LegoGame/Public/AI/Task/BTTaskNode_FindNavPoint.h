// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindNavPoint.generated.h"

/**
 * 
 */
UCLASS()
class LEGOGAME_API UBTTaskNode_FindNavPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTaskNode_FindNavPoint();

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector OriginPosKey;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetPosKey;
	UPROPERTY(EditAnywhere)
	float NavRadius;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
};
