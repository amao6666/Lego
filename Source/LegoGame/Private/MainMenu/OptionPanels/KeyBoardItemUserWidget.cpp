// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/OptionPanels/KeyBoardItemUserWidget.h"
#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"
#include "GameFramework/InputSettings.h"

void UKeyBoardItemUserWidget::ChangeKeyBoardInfo(FText BoardName, FKey Key, FName OutKeyEventName, float OutKeyScale)
{
	KeyStringTextBlock->SetText(BoardName);
	KeySelector->SelectedKey = Key;
	CurrentKey = Key;
	KeyEventName = OutKeyEventName;
	KeyScale = OutKeyScale;
}

void UKeyBoardItemUserWidget::SetInputKey(FKey NewKey)
{
	//键值更新到用户输入配置表里
	if (KeyScale == 0) //说明是action事件
	{
		FInputActionKeyMapping KeyMapping;
		KeyMapping.Key = CurrentKey;
		KeyMapping.ActionName = KeyEventName;
		UInputSettings::GetInputSettings()->RemoveActionMapping(KeyMapping);
		KeyMapping.Key = NewKey;
		UInputSettings::GetInputSettings()->AddActionMapping(KeyMapping);
	}
	else //说明时轴事件
	{
		FInputAxisKeyMapping KeyMapping;
		KeyMapping.Key = CurrentKey;
		KeyMapping.Scale = KeyScale;
		KeyMapping.AxisName = KeyEventName;
		UInputSettings::GetInputSettings()->RemoveAxisMapping(KeyMapping);
		KeyMapping.Key = NewKey;
		UInputSettings::GetInputSettings()->AddAxisMapping(KeyMapping);
	}
	CurrentKey = NewKey;
}

void UKeyBoardItemUserWidget::SetKeySelector(FKey NewKey)
{
	KeySelector->SetSelectedKey(NewKey);
}

void UKeyBoardItemUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//绑定事件通知
	KeySelector->OnKeySelected.AddDynamic(this, &UKeyBoardItemUserWidget::OnKeySelected);
}

void UKeyBoardItemUserWidget::OnKeySelected(FInputChord SelectedKey)
{
	if (CurrentKey == SelectedKey.Key)//说明当前的键值和你拾取的键值一致，无需重复设置
	{
		return;
	}

	//查重
	auto ActionMappings = UInputSettings::GetInputSettings()->GetActionMappings();
	for (auto Action : ActionMappings)
	{
		if (Action.Key == SelectedKey.Key)//找到了相同的
		{
			KeySelector->SetSelectedKey(CurrentKey);
			return;
		}
	}

	auto AxisMappings = UInputSettings::GetInputSettings()->GetAxisMappings();
	for (auto Axis : AxisMappings)
	{
		if (Axis.Key == SelectedKey.Key)
		{
			KeySelector->SetSelectedKey(CurrentKey);
			return;
		}
	}
	
	//键值更新到用户输入配置表里
	if (KeyScale == 0)//说明是action事件
	{
		FInputActionKeyMapping KeyMapping;
		KeyMapping.Key = CurrentKey;
		KeyMapping.ActionName = KeyEventName;
		UInputSettings::GetInputSettings()->RemoveActionMapping(KeyMapping);
		KeyMapping.Key = SelectedKey.Key;
		UInputSettings::GetInputSettings()->AddActionMapping(KeyMapping);
	}
	else//说明时轴事件
	{
		FInputAxisKeyMapping KeyMapping;
		KeyMapping.Key = CurrentKey;
		KeyMapping.Scale = KeyScale;
		KeyMapping.AxisName = KeyEventName;
		UInputSettings::GetInputSettings()->RemoveAxisMapping(KeyMapping);
		KeyMapping.Key = SelectedKey.Key;
		UInputSettings::GetInputSettings()->AddAxisMapping(KeyMapping);
	}

	CurrentKey = SelectedKey.Key;
}