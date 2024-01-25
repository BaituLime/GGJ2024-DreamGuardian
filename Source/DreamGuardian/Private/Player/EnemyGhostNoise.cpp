// Copyright Baitulime. All Rights Reserved.


#include "Player/EnemyGhostNoise.h"


// Sets default values
AEnemyGhostNoise::AEnemyGhostNoise()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyGhostNoise::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyGhostNoise::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyGhostNoise::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

