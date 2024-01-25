// Copyright Baitulime. All Rights Reserved.


#include "Player/EnemyGhostRemote.h"


// Sets default values
AEnemyGhostRemote::AEnemyGhostRemote()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyGhostRemote::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyGhostRemote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyGhostRemote::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

