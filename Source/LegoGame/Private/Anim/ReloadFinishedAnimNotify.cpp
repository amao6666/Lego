// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/ReloadFinishedAnimNotify.h"
#include "Character/LGCharacterBase.h"
#include "Weapon/WeaponActor.h"

void UReloadFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(MeshComp->GetOwner()))
	{
		if (CharacterBase->GetHoldWeapon())
		{
			CharacterBase->GetHoldWeapon()->FinishReload();
		}
	}
}
