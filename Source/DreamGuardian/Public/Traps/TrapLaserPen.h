// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "TrapLaserPen.generated.h"

UCLASS()
class DREAMGUARDIAN_API ATrapLaserPen : public ATrap
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrapLaserPen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
