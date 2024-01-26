// Copyright Baitulime. All Rights Reserved.


#include "Player/Enemy.h"

#include "DreamGuardian/PrintString.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	ValueHealth = MaxValueHealth;
	GetCharacterMovement()->MaxWalkSpeed = SpeedMoving;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
