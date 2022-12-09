// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/LGAIController.h"
#include "Enemy/LGEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void ALGAIController::OnPossess(APawn* InPawn)
{

	Super::OnPossess(InPawn);
	//检查当前控制的是EnemyCharacter么 启用行为树
	if (ALGEnemyCharacter* EnemyCharacter = Cast<ALGEnemyCharacter>(InPawn))
	{
		RunBehaviorTree(EnemyCharacter->GetBehaviorTree());

		//添加测试
		GetBlackboardComponent()->SetValueAsVector(TEXT("FindPos"), InPawn->GetActorLocation() + InPawn->GetActorForwardVector() * 1000);
		GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPos"), InPawn->GetActorLocation());
	}
}
