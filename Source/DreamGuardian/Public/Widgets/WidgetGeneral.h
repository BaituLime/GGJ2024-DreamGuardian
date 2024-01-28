// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetGeneral.generated.h"

class UHorizontalBox;
class UTextBlock;
class UProgressBar;
class UImage;
/**
 * 
 */
UCLASS()
class DREAMGUARDIAN_API UWidgetGeneral : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBarHealth;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlockDreamCount;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlockActionName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlockDescription;
	UPROPERTY(meta=(BindWidget))
	UImage* ImageQ;
	UPROPERTY(meta=(BindWidget))
	UImage* ImageW;
	UPROPERTY(meta=(BindWidget))
	UImage* ImageE;
	UPROPERTY(meta=(BindWidget))
	UImage* ImageR;
	UPROPERTY(meta=(BindWidget))
	UImage* ImageM;
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HorizontalBoxTips;

public:
	void SetHealthPercent(const float Value);
	void SetDreamCount(const float Dream);
	void DisplaySkill(const int Index);
	void OpenTips();
	void CloseTips();

protected:
	virtual void NativeConstruct() override;
};
