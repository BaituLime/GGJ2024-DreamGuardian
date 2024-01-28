// Copyright Baitulime. All Rights Reserved.


#include "Widgets/WidgetFailure.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameMode/GameModeBattle.h"
#include "Kismet/GameplayStatics.h"

void UWidgetFailure::SetDreamAwake(const float Dream, const float Awake)
{
	TextBlockScore->SetText(FText::FromString(FString::Printf(TEXT("Sweet Dream: %.2f, Awake: %.2f"), Dream, Awake)));
}