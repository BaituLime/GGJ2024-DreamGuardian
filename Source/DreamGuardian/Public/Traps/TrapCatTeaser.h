﻿// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "TrapCatTeaser.generated.h"

UCLASS()
class DREAMGUARDIAN_API ATrapCatTeaser : public ATrap
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrapCatTeaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
