// Fill out your copyright notice in the Description page of Project Settings.


#include "LegoGameMode.h"

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
