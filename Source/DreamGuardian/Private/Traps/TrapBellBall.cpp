// Copyright Baitulime. All Rights Reserved.


#include "Traps/TrapBellBall.h"


// Sets default values
ATrapBellBall::ATrapBellBall()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrapBellBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapBellBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATrapBellBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

