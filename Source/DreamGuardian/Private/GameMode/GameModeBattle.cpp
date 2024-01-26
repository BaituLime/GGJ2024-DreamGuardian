// Copyright Baitulime. All Rights Reserved.

#include "GameMode/GameModeBattle.h"
#include "Player/CatPlayerController.h"
#include "Player/CatCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameModeBattle::AGameModeBattle()
{
}

void AGameModeBattle::OnFailure()
{
}

void AGameModeBattle::AddCoin(const float Value)
{
	ValueCoin += Value;
}
