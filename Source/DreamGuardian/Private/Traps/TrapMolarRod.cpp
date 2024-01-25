// Copyright Baitulime. All Rights Reserved.


#include "Traps/TrapMolarRod.h"


// Sets default values
ATrapMolarRod::ATrapMolarRod()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrapMolarRod::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapMolarRod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATrapMolarRod::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

