// Fill out your copyright notice in the Description page of Project Settings.


#include "LegoGameHUD.h"

#include "Character/LGCharacterBase.h"
#include "UMG/PackageUserWidget.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

ALegoGameHUD::ALegoGameHUD()
{
	PackageUI = nullptr;
}

void ALegoGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALegoGameHUD::TogglePackageShow()
{
	if (!PackageUI)
	{
		TSubclassOf<UPackageUserWidget> Package = LoadClass<UPackageUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Lego/UMG/UMG_Package.UMG_Package_C'"));
		PackageUI = CreateWidget<UPackageUserWidget>(UGameplayStatics::GetPlayerController(this, 0), Package);
	}
	if (!(PackageUI->IsInViewport()))
	{
		PackageUI->AddToViewport();
		UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
	}
	else
	{
		PackageUI->RemoveFromParent();
		UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(false);
	}
}

void ALegoGameHUD::DrawHUD()
{
	Super::DrawHUD();
	if (ALGCharacterBase* CharacterBase = Cast<ALGCharacterBase>(GetOwningPawn()))
	{
		if (CharacterBase->IsHoldWeapon())
		{
			//绘制准星
			float CenterX = Canvas->ClipX / 2;
			float CenterY = Canvas->ClipY / 2;

			float AimSignOffset = 8;
			float AimSignLen = 15;

			//上下
			DrawLine(CenterX, CenterY - AimSignOffset - AimSignLen, CenterX, CenterY - AimSignOffset, FLinearColor::Yellow);
			DrawLine(CenterX, CenterY + AimSignOffset + AimSignLen, CenterX, CenterY + AimSignOffset, FLinearColor::Yellow);

			//左右
			DrawLine(CenterX - AimSignOffset - AimSignLen, CenterY, CenterX - AimSignOffset, CenterY, FLinearColor::Yellow);
			DrawLine(CenterX + AimSignOffset + AimSignLen, CenterY, CenterX + AimSignOffset, CenterY, FLinearColor::Yellow);

			//绘制弹夹容积
			CharacterBase->GetHoldWeapon()->GetMaxBulletNumber();

			DrawText(FString::Printf(TEXT("%d/%d"), CharacterBase->GetHoldWeapon()->GetCurrentBulletNumber(), CharacterBase->GetHoldWeapon()->GetMaxBulletNumber()), FLinearColor::Red,
				200, 200);

			
		}
	}
}
