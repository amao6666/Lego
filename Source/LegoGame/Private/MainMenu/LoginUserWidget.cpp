// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/LoginUserWidget.h"

#include "MainMenu/MainMenuHUD.h"
#include "MainMenu/AccountSaveGame.h"
#include "Components/CheckBox.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void ULoginUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SaveGameSlotName = TEXT("AccountSlot");
	LoadAccount();
	if (AccountSaveGame)
	{
		SaveCheckBox->SetCheckedState(ECheckBoxState::Checked);
		EditableTextAccount->SetText(FText::FromString(AccountSaveGame->LoginAccount));
		EditableTextPassword->SetText(FText::FromString(AccountSaveGame->LoginPassword));
	}
}

void ULoginUserWidget::LoginAccount()
{

	if (SaveCheckBox->IsChecked())
	{
		SaveAccount();
	}
	else
	{
		// remove game date from local
		UGameplayStatics::DeleteGameInSlot(SaveGameSlotName, 0);
	}
	
	AMainMenuHUD* MainMenuHUD = Cast<AMainMenuHUD>(GetOwningPlayer()->GetHUD());
	if (MainMenuHUD)
	{
		//MainMenuHUD->SetMainMenuShow(false);
		MainMenuHUD->SetRoomListShow(true);
	}
	RemoveFromParent();
}

void ULoginUserWidget::SaveAccount()
{
	if (!AccountSaveGame)
	{
		AccountSaveGame = Cast<UAccountSaveGame>(UGameplayStatics::CreateSaveGameObject(UAccountSaveGame::StaticClass()));
	}
	AccountSaveGame->LoginAccount = EditableTextAccount->GetText().ToString();
	AccountSaveGame->LoginPassword = EditableTextPassword->GetText().ToString();
	// save account game to local
	UGameplayStatics::SaveGameToSlot(AccountSaveGame, SaveGameSlotName, 0);
}

void ULoginUserWidget::LoadAccount()
{
	if (!AccountSaveGame)
	{
		if (UGameplayStatics::DoesSaveGameExist(SaveGameSlotName, 0))
		{
			AccountSaveGame = Cast<UAccountSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0));
		}
	}
}

