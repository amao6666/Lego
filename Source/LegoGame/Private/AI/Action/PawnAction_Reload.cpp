// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Action/PawnAction_Reload.h"
#include "AIController.h"
#include "Character/LGCharacterBase.h"
#include "Weapon/WeaponActor.h"

UPawnAction_Reload::UPawnAction_Reload()
{
	bBlockTask = true;
}

bool UPawnAction_Reload::Start()
{
	Super::Start();
	//获取角色
	if (ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(BrainComp->GetAIOwner()->GetPawn()))
	{
		if (!CharacterBase->IsHoldWeapon())
		{
			return false;
		}
		float WaitTime = CharacterBase->GetHoldWeapon()->ReloadBullets();
		if (!bBlockTask)
		{
			Finish(EPawnActionResult::Success);
		}
		else
		{
			//启用定时器
			if (WaitTime > 0)
			{
				FTimerHandle Handle;
				BrainComp->GetAIOwner()->GetWorld()->GetTimerManager().SetTimer(Handle, this, &UPawnAction_Reload::ReloadEndCallBack, WaitTime);
			}
		}
	}
	return true;
}

void UPawnAction_Reload::ReloadEndCallBack()
{
	Finish(EPawnActionResult::Success);
}
