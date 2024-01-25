// Copyright Baitulime. All Rights Reserved.


#include "GameMode/Human.h"


AHuman::AHuman()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHuman::BeginPlay()
{
	Super::BeginPlay();
}

void AHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

