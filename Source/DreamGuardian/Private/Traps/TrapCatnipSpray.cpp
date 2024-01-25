// Copyright Baitulime. All Rights Reserved.


#include "Traps/TrapCatnipSpray.h"


// Sets default values
ATrapCatnipSpray::ATrapCatnipSpray()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrapCatnipSpray::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapCatnipSpray::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATrapCatnipSpray::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

