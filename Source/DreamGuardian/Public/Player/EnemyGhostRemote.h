// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyGhostRemote.generated.h"

UCLASS()
class DREAMGUARDIAN_API AEnemyGhostRemote : public AEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyGhostRemote();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
