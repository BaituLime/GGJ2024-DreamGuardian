// Copyright Baitulime. All Rights Reserved.


#include "Widgets/WidgetHuman.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidgetHuman::SetDreamAwake(const float Dream, const float Awake)
{
	TextBlockSweetDream->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), Dream)));
	ProgressBarAwake->SetPercent(Awake / 100.f);
}
