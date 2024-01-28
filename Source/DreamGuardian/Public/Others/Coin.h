// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class USphereComponent;
class UWidgetComponent;

UCLASS()
class DREAMGUARDIAN_API ACoin : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = Coin)
	USoundBase* SoundAppear;
	UPROPERTY(EditAnywhere, Category = Coin)
	USoundBase* SoundPick;
	
private:
	UPROPERTY(VisibleAnywhere, Category = Coin)
	float ValueCurrent{1};

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent;


public:
	ACoin();

protected:
	virtual void BeginPlay() override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
