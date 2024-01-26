// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Human.generated.h"

UCLASS()
class DREAMGUARDIAN_API AHuman : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Appearance")
	TSubclassOf<UUserWidget> WidgetClassFailure;

private:
	float ValueSweetDream;
	float ValueQuiet;
	
	UPROPERTY(VisibleAnywhere)
	UUserWidget* WidgetFailure;
	
public:
	AHuman();
	virtual void Tick(float DeltaTime) override;

	void DecreaseSweetDreamValue(const float Value);
	void DecreaseQuietValue(const float Value);

protected:
	virtual void BeginPlay() override;

private:
	void OnFailure();
};

