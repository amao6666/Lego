// Fill out your copyright notice in the Description page of Project Settings.


#include "LegoGameMode.h"
#include "LegoGame/LegoGame.h"
#include "LegoGameHUD.h"
#include "Player/LGPlayerCharacter.h"
#include "Player/LGPlayerController.h"

ALegoGameMode::ALegoGameMode()
{
	ConstructorHelpers::FClassFinder<ALGPlayerCharacter> PlayerClassFinder(TEXT("Blueprint'/Game/Lego/Blueprint/Player/BP_Player.BP_Player_C'"));
	DefaultPawnClass = PlayerClassFinder.Class;
	PlayerControllerClass = ALGPlayerController::StaticClass();

	HUDClass = ALegoGameHUD::StaticClass();
}

void ALegoGameMode::BeginPlay()
{
	Super::BeginPlay();
	// 重置引擎阵营匹配规则
	FGenericTeamId::SetAttitudeSolver([](FGenericTeamId A, FGenericTeamId B)
	{
		if (A == TeamID_Yellow || B == TeamID_Yellow)
		{
			return ETeamAttitude::Neutral;
		}
		return A != B ? ETeamAttitude::Hostile : ETeamAttitude::Friendly;
	});
}
