// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/Widget/WaitingUserWidget.h"

void UWaitingUserWidget::AutoClose(int WaitSeconds)
{
	RemainSeconds = WaitSeconds;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWaitingUserWidget::TimerCallback, 1, true);
	ChangeWaitingText();
}

void UWaitingUserWidget::ChangeWaitingText()
{
	WaitingTextBlock->SetText(FText::Format(NSLOCTEXT("WaitUI", "k1", "请等待({0})"), FText::AsNumber(RemainSeconds)));
}

void UWaitingUserWidget::TimerCallback()
{
	if (--RemainSeconds < 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		RemoveFromParent();
		return;
	}
	ChangeWaitingText();
}
