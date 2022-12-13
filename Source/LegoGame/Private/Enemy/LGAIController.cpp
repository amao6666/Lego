// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/LGAIController.h"
#include "Enemy/LGEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Character/LGCharacterBase.h"
#include "LegoGame/LegoGame.h"

ALGAIController::ALGAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AiPerceptionComp"));
}

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

ETeamAttitude::Type ALGAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// if (const ALGCharacterBase* OtherCharacter = Cast<const ALGCharacterBase>(&Other))
	// {
	// 	if (ALGCharacterBase* MyCharacter = Cast<ALGCharacterBase>(GetPawn()))
	// 	{
	// 		if (OtherCharacter->GetTeamColor() == ETeamColor::ETC_Yellow || MyCharacter->GetTeamColor() == ETeamColor::ETC_Yellow)
	// 		{
	// 			return ETeamAttitude::Neutral;
	// 		}
	// 		return OtherCharacter->GetTeamColor() == MyCharacter->GetTeamColor() ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
	// 	}
	// }
	// return ETeamAttitude::Neutral;
	if (IGenericTeamAgentInterface* MyTeamAgent = Cast<IGenericTeamAgentInterface>(GetPawn()))
	{
		if (const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other))
		{
			return FGenericTeamId::GetAttitude(MyTeamAgent->GetGenericTeamId(), OtherTeamAgent->GetGenericTeamId());
		}
	}
	return ETeamAttitude::Neutral;
}

FGenericTeamId ALGAIController::GetGenericTeamId() const
{
	if (TeamColor == ETeamColor::ETC_Blue)
	{
		return TeamID_Blue;
	}
	else if (TeamColor == ETeamColor::ETC_Yellow)
	{
		return TeamID_Yellow;
	}
	return TeamID_Red;
}
