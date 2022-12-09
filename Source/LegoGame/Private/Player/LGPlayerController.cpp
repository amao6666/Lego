// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LGPlayerController.h"

#include "Manager/LGPlayerCameraManager.h"

ALGPlayerController::ALGPlayerController()
{
	PlayerCameraManagerClass = ALGPlayerCameraManager::StaticClass();
}
