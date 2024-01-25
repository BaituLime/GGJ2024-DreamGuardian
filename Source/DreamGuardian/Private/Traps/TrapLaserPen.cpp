// Copyright Baitulime. All Rights Reserved.


#include "Traps/TrapLaserPen.h"


// Sets default values
ATrapLaserPen::ATrapLaserPen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrapLaserPen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapLaserPen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

