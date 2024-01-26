﻿// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "TrapMolarRod.generated.h"

UCLASS()
class DREAMGUARDIAN_API ATrapMolarRod : public ATrap
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrapMolarRod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
