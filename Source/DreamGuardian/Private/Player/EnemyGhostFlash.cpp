// Copyright Baitulime. All Rights Reserved.


#include "Player/EnemyGhostFlash.h"


// Sets default values
AEnemyGhostFlash::AEnemyGhostFlash()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyGhostFlash::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyGhostFlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyGhostFlash::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

