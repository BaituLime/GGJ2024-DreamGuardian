// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetHuman.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class DREAMGUARDIAN_API UWidgetHuman : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlockSweetDream;
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBarAwake;

public:
	UFUNCTION()
	void SetDreamAwake(const float Dream, const float Awake);
};
