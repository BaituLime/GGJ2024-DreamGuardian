// Copyright Baitulime. All Rights Reserved.


#include "Traps/TrapCatTeaser.h"


// Sets default values
ATrapCatTeaser::ATrapCatTeaser()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrapCatTeaser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapCatTeaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATrapCatTeaser::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

