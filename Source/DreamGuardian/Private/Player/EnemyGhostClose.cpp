// Copyright Baitulime. All Rights Reserved.


#include "Player/EnemyGhostClose.h"


// Sets default values
AEnemyGhostClose::AEnemyGhostClose()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyGhostClose::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyGhostClose::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyGhostClose::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

