// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/RegistUserWidget.h"

void URegistUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SendCodeButton->OnClicked.AddDynamic(this, &URegistUserWidget::OnSendCodeButtonClicked);
}

void URegistUserWidget::OnSendCodeButtonClicked()
{
	if (!ValidationEmail())
	{
		return;
	}
	SendCodeSecond = 5;
	// set button to not disabled
	SendCodeButton->SetIsEnabled(false);
	// start timer
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &URegistUserWidget::SendCodeTimerCallback, 1, true);
	SendCodeButtonText->SetText(FText::Format(NSLOCTEXT("RegistUI", "k1", "发送({0})"), FText::AsNumber(SendCodeSecond)));
}

void URegistUserWidget::SendCodeTimerCallback()
{
	if (--SendCodeSecond < 0)
	{
		RestSendCodeButton();
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
	else
	{
		SendCodeButtonText->SetText(FText::Format(NSLOCTEXT("RegistUI", "k1", "发送({0})"), FText::AsNumber(SendCodeSecond)));
	}
}

void URegistUserWidget::RestSendCodeButton()
{
	SendCodeSecond = 5;
	SendCodeButton->SetIsEnabled(true);
	SendCodeButtonText->SetText(NSLOCTEXT("RegistUI", "k2", "发送"));
}

bool URegistUserWidget::ValidationEmail()
{
	// check email by Regex
	FRegexPattern Pattern(TEXT("^\\w{1,10}@\\w{1,6}\\.\\w{2,6}$"));
	FRegexMatcher Matcher(Pattern, EditableTextEmail->GetText().ToString());
	return Matcher.FindNext();
}
