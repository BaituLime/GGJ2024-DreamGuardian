// Copyright Baitulime. All Rights Reserved.


#include "Widgets/WidgetGeneral.h"

#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidgetGeneral::SetHealthPercent(const float Value)
{
	ProgressBarHealth->SetPercent(Value);
}

void UWidgetGeneral::SetDreamCount(const float Dream)
{
	TextBlockDreamCount->SetText(FText::FromString(FString::Printf(TEXT("%.2f"),Dream)));
}

void UWidgetGeneral::DisplaySkill(const int Index)
{
	switch (Index)
	{
	case 0:
		ImageQ->SetVisibility(ESlateVisibility::Collapsed);
		ImageW->SetVisibility(ESlateVisibility::Visible);
		ImageE->SetVisibility(ESlateVisibility::Visible);
		ImageR->SetVisibility(ESlateVisibility::Visible);
		ImageM->SetVisibility(ESlateVisibility::Visible);
		TextBlockActionName->SetText(FText::FromString(TEXT("Pounce")));
		TextBlockDescription->SetText(FText::FromString(TEXT("The cat pounces on the enemy, dealing 70 points of damage to a single target. Base Awake Value increase: 10 points.")));
		break;
	case 1:
		ImageQ->SetVisibility(ESlateVisibility::Visible);
		ImageW->SetVisibility(ESlateVisibility::Collapsed);
		ImageE->SetVisibility(ESlateVisibility::Visible);
		ImageR->SetVisibility(ESlateVisibility::Visible);
		ImageM->SetVisibility(ESlateVisibility::Visible);
		TextBlockActionName->SetText(FText::FromString(TEXT("Holy Cat Light")));
		TextBlockDescription->SetText(FText::FromString(TEXT("The cat's belly emits light, dealing 50 points of damage to all enemies in a 60-degree fan-shaped area in front of it. Base Awake Value increase: 20 points.")));
		break;
	case 2:
		ImageQ->SetVisibility(ESlateVisibility::Visible);
		ImageW->SetVisibility(ESlateVisibility::Visible);
		ImageE->SetVisibility(ESlateVisibility::Collapsed);
		ImageR->SetVisibility(ESlateVisibility::Visible);
		ImageM->SetVisibility(ESlateVisibility::Visible);
		TextBlockActionName->SetText(FText::FromString(TEXT("Midnight Cat Disco")));
		TextBlockDescription->SetText(FText::FromString(TEXT("The cat starts disco dancing, causing all demons on the field to dance together for 5 seconds and unable to move. Base Awake Value increase: 40 points.")));
		break;
	case 3:
		ImageQ->SetVisibility(ESlateVisibility::Visible);
		ImageW->SetVisibility(ESlateVisibility::Visible);
		ImageE->SetVisibility(ESlateVisibility::Visible);
		ImageR->SetVisibility(ESlateVisibility::Collapsed);
		ImageM->SetVisibility(ESlateVisibility::Visible);
		TextBlockActionName->SetText(FText::FromString(TEXT("GET AWAY FROM MY FRIEND")));
		TextBlockDescription->SetText(FText::FromString(TEXT("The cat releases a huge flash, the player's screen turns completely white, and all demons on the field are killed. Base Awake Value increase: 60 points.")));
		break;
	case 4:
		ImageQ->SetVisibility(ESlateVisibility::Visible);
		ImageW->SetVisibility(ESlateVisibility::Visible);
		ImageE->SetVisibility(ESlateVisibility::Visible);
		ImageR->SetVisibility(ESlateVisibility::Visible);
		ImageM->SetVisibility(ESlateVisibility::Collapsed);
		TextBlockActionName->SetText(FText::FromString(TEXT("Normal Attack")));
		TextBlockDescription->SetText(FText::FromString(TEXT("The cat punches the enemy, dealing 30 points of damage to a single target.")));
		break;
	default:
		TextBlockActionName->SetText(FText::GetEmpty());
		TextBlockDescription->SetText(FText::GetEmpty());
		ImageQ->SetVisibility(ESlateVisibility::Visible);
		ImageW->SetVisibility(ESlateVisibility::Visible);
		ImageE->SetVisibility(ESlateVisibility::Visible);
		ImageR->SetVisibility(ESlateVisibility::Visible);
		ImageM->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWidgetGeneral::OpenTips()
{
	HorizontalBoxTips->SetVisibility(ESlateVisibility::Visible);
}

void UWidgetGeneral::CloseTips()
{
	HorizontalBoxTips->SetVisibility(ESlateVisibility::Collapsed);
}

void UWidgetGeneral::NativeConstruct()
{
	Super::NativeConstruct();

	HorizontalBoxTips->SetVisibility(ESlateVisibility::Collapsed);
	TextBlockActionName->SetText(FText::GetEmpty());
	TextBlockDescription->SetText(FText::GetEmpty());
	ImageQ->SetVisibility(ESlateVisibility::Visible);
	ImageW->SetVisibility(ESlateVisibility::Visible);
	ImageE->SetVisibility(ESlateVisibility::Visible);
	ImageR->SetVisibility(ESlateVisibility::Visible);
	ImageM->SetVisibility(ESlateVisibility::Visible);
}
