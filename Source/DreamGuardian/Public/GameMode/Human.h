// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Human.generated.h"

class UWidgetFailure;
class UWidgetComponent;
class UWidgetHuman;
class UBoxComponent;

UCLASS()
class DREAMGUARDIAN_API AHuman : public AActor
{
	GENERATED_BODY()

public:
	friend class ACatPlayerController;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Appearance")
	TSubclassOf<UUserWidget> WidgetClassFailure;

private:
	UPROPERTY(VisibleAnywhere)
	bool bIsDead;
	UPROPERTY(VisibleAnywhere)
	float ValueSweetDream{100.f};
	UPROPERTY(VisibleAnywhere)
	float ValueAwake{0.f};

	UPROPERTY(VisibleAnywhere, Category = "Appearance")
	UWidgetFailure* WidgetFailure;
	UPROPERTY(VisibleAnywhere, Category = "Appearance")
	UWidgetHuman* WidgetHuman;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent;

public:
	AHuman();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DecreaseSweetDreamValue(const float Value);
	UFUNCTION(BlueprintCallable)
	void DecreaseQuietValue(const float Value);

protected:
	virtual void BeginPlay() override;

private:
	void OnFailure();
};
