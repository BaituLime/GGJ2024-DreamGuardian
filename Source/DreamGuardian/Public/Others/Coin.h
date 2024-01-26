// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class UCapsuleComponent;

UCLASS()
class DREAMGUARDIAN_API ACoin : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = Coin)
	float ValueCurrent{1};

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

public:
	ACoin();

	void SetCurrentValue(const float Value);

protected:
	virtual void BeginPlay() override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
