// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/OptionPanels/KeyMapUserWidget.h"
#include "GameFramework/InputSettings.h"
#include "MainMenu/OptionPanels/KeyBoardItemUserWidget.h"
#include "Components/VerticalBox.h"

void UKeyMapUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	TSubclassOf<UKeyBoardItemUserWidget> KeyBoardClass = LoadClass<UKeyBoardItemUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Lego/MainMenu/UMG/OptionPanels/Widget_KeyBoardItem.Widget_KeyBoardItem_C'"));

	//加载表格
	if (!KeyInfoDT)
	{
		KeyInfoDT = LoadObject<UDataTable>(this, TEXT("DataTable'/Game/Lego/Data/UI/DT_KeyInfo.DT_KeyInfo'"));
	}
	TArray<FWidgetKeyInfo*> KeyInfos;
	KeyInfoDT->GetAllRows<FWidgetKeyInfo>(TEXT("解析数据表格错误！！KeyInfo表格"), KeyInfos);

	//根据当前用户的按键配置更新按键面板
	const TArray<FInputActionKeyMapping> KeyMappings = UInputSettings::GetInputSettings()->GetActionMappings();
	for (auto Key : KeyMappings)
	{
		UKeyBoardItemUserWidget* KeyBoardWidget = CreateWidget<UKeyBoardItemUserWidget>(GetOwningPlayer(), KeyBoardClass);
		for (auto Info : KeyInfos)
		{
			if (Info->KeyEventName == Key.ActionName)
			{
				KeyBoardWidget->ChangeKeyBoardInfo(Info->KeyEventDescription, Key.Key, Key.ActionName, 0);
				break;
			}
		}
		KeysVerticalBox->AddChild(KeyBoardWidget);
	}

	//配置显示轴事件按键信息
	const TArray<FInputAxisKeyMapping> AxisKeyMappings = UInputSettings::GetInputSettings()->GetAxisMappings();

	for (auto Axis : AxisKeyMappings)
	{
		UKeyBoardItemUserWidget* KeyBoardWidget = CreateWidget<UKeyBoardItemUserWidget>(GetOwningPlayer(), KeyBoardClass);
		for (auto Info : KeyInfos)
		{
			if (Info->KeyEventName == Axis.AxisName && Info->Scale == Axis.Scale)
			{
				KeyBoardWidget->ChangeKeyBoardInfo(Info->KeyEventDescription, Axis.Key, Axis.AxisName, Axis.Scale);
				break;
			}
		}
		KeysVerticalBox->AddChild(KeyBoardWidget);
	}
}

void UKeyMapUserWidget::ResetAllKey()
{
	if (!KeyInfoDT)
	{
		KeyInfoDT = LoadObject<UDataTable>(this, TEXT("DataTable'/Game/Lego/Data/UI/DT_KeyInfo.DT_KeyInfo'"));
	}
	TArray<FWidgetKeyInfo*> KeyInfos;
	KeyInfoDT->GetAllRows<FWidgetKeyInfo>(TEXT("解析数据表格错误！！KeyInfo表格"), KeyInfos);
	
	//获取到所有的UI板子
	for(int32 i =0; i<KeysVerticalBox->GetChildrenCount(); i++)
	{
		if (UKeyBoardItemUserWidget* KeyBoardWidget = Cast<UKeyBoardItemUserWidget>(KeysVerticalBox->GetChildAt(i)))
		{
			for (auto KeyInfo : KeyInfos)
			{
				if (KeyInfo->KeyEventName == KeyBoardWidget->GetKeyEventName() && KeyInfo->Scale == KeyBoardWidget->GetKeyScale())
				{
					if (KeyInfo->Key != KeyBoardWidget->GetCurrentKey())
					{
						KeyBoardWidget->SetInputKey(KeyInfo->Key);
						KeyBoardWidget->SetKeySelector(KeyInfo->Key);
					}
					break;
				}
			}
		}
	}
}
