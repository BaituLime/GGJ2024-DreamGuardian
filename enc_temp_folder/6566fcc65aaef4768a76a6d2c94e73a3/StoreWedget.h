// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

#include "GameFramework/PlayerController.h"


#include "StoreWedget.generated.h"
/**
 * 
 */
UCLASS()
class DREAMGUARDIAN_API UStoreWedget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* skillButton;

	UPROPERTY(meta = (BindWidget))
	UButton* propertyButton;

	UPROPERTY(meta = (BindWidget))
	UButton* weaponButton;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* switchCanvas;

	UFUNCTION()
	void open();

private:
	UFUNCTION()
	void start();
};
