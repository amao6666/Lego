// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LGPlayerController.h"

#include "LegoGame/LegoGame.h"
#include "Manager/LGPlayerCameraManager.h"

ALGPlayerController::ALGPlayerController()
{
	PlayerCameraManagerClass = ALGPlayerCameraManager::StaticClass();
}

FGenericTeamId ALGPlayerController::GetGenericTeamId() const
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
