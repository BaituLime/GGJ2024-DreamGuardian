// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetFailure.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DREAMGUARDIAN_API UWidgetFailure : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlockScore;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> TitleMap;

public:
	void SetDreamAwake(const float Dream, const float Awake);
};
