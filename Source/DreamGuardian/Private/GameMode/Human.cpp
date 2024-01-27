// Copyright Baitulime. All Rights Reserved.


#include "GameMode/Human.h"

#include "DreamGuardian/PrintString.h"
#include "GameMode/GameModeBattle.h"
#include "Kismet/GameplayStatics.h"


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

void AHuman::DecreaseSweetDreamValue(const float Value)
{
	ValueSweetDream -= Value;
	if (ValueSweetDream <= 0)
		OnFailure();
}

void AHuman::DecreaseQuietValue(const float Value)
{
	ValueQuiet -= Value;
	if (ValueQuiet <= 0)
		OnFailure();
}

void AHuman::OnFailure()
{
	// TODO: AHuman::OnFailure
	Print("AHuman::OnFailure")
	AGameModeBattle* GameModeBattle = Cast<AGameModeBattle>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeBattle->OnFailure();
}
