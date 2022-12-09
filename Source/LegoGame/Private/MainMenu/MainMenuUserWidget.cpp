// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenuUserWidget.h"
#include "MainMenu/OptionUserWidget.h"
#include "MainMenu/LoginUserWidget.h"

void UMainMenuUserWidget::ShowGameSettingPanel()
{
	if (!OptionUI)
	{
		TSubclassOf<UOptionUserWidget> OptionUIClass = LoadClass<UOptionUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Lego/MainMenu/UMG/UMG_Option.UMG_Option_C'"));
		OptionUI = CreateWidget<UOptionUserWidget>(GetOwningPlayer(), OptionUIClass);
	}
	if (OptionUI && !OptionUI->IsInViewport())
	{
		OptionUI->AddToViewport();
	}
}

void UMainMenuUserWidget::ShowLoginPanel()
{
	if (!LoginUI)
	{
		TSubclassOf<ULoginUserWidget> LoginUIClass = LoadClass<ULoginUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Lego/MainMenu/UMG/UMG_Login.UMG_Login_C'"));
		LoginUI = CreateWidget<ULoginUserWidget>(GetOwningPlayer(), LoginUIClass);
	}
	if (LoginUI && !LoginUI->IsInViewport())
	{
		LoginUI->AddToViewport();
	}
}
