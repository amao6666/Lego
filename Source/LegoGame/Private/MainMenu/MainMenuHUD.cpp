// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenuHUD.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenu/MainMenuUserWidget.h"
#include "MainMenu/RoomListUserWidget.h"
#include "MainMenu/Widget/WaitingUserWidget.h"

AMainMenuHUD::AMainMenuHUD()
{
	// load MainMenuUI Class
	ConstructorHelpers::FClassFinder<UMainMenuUserWidget> MainMenu(TEXT("WidgetBlueprint'/Game/Lego/MainMenu/UMG/UMG_MainMenu.UMG_MainMenu_C'"));
	MainMenuUI = CreateWidget<UMainMenuUserWidget>(UGameplayStatics::GetPlayerController(this, 0), MainMenu.Class);
	// load RoomListUI Class
	ConstructorHelpers::FClassFinder<URoomListUserWidget> RoomList(TEXT("WidgetBlueprint'/Game/Lego/MainMenu/UMG/UMG_RoomList.UMG_RoomList_C'"));
	RoomListUI = CreateWidget<URoomListUserWidget>(UGameplayStatics::GetPlayerController(this, 0), RoomList.Class);
	// load WaitUI Class
	ConstructorHelpers::FClassFinder<UWaitingUserWidget> Waiting(TEXT("WidgetBlueprint'/Game/Lego/MainMenu/UMG/Widget/Widget_Waiting.Widget_Waiting_C'"));
	WaitingUI = CreateWidget<UWaitingUserWidget>(UGameplayStatics::GetPlayerController(this, 0), Waiting.Class);
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MainMenuUI && !MainMenuUI->IsInViewport())
	{
		MainMenuUI->AddToViewport();
		UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
	}
}

void AMainMenuHUD::SetMainMenuShow(bool bIsShow)
{
	if (MainMenuUI)
	{
		bIsShow ? MainMenuUI->AddToViewport() : MainMenuUI->RemoveFromParent();
	}
}

void AMainMenuHUD::SetRoomListShow(bool bIsShow)
{
	if (RoomListUI)
	{
		bIsShow ? RoomListUI->AddToViewport() : RoomListUI->RemoveFromParent();
	}
}

void AMainMenuHUD::SetWaitingShow(bool bIsShow, bool bIsAutoClose, int32 WaitSeconds)
{
	if (WaitingUI)
	{
		if (bIsShow)
		{
			WaitingUI->AddToViewport();
			if (bIsAutoClose) WaitingUI->AutoClose(WaitSeconds);
		}
		else
		{
			WaitingUI->RemoveFromParent();
		}
	}
}
