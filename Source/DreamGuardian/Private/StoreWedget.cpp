// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreWedget.h"

void UStoreWedget::open()
{
	/*skillButton->OnClicked.AddDynamic(this, &UStoreWedget::start());*/
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (!pc)
		return;
	FInputModeUIOnly uionly;
	uionly.SetWidgetToFocus(TakeWidget());
	uionly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	pc->SetInputMode(uionly);
	pc->SetShowMouseCursor(true);
}

void UStoreWedget::start()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("111"));
}
