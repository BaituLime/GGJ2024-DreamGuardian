// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBattle.generated.h"

UCLASS(minimalapi)
class AGameModeBattle : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Game Status")
	float ValueCoin{0};

public:
	friend class ACatPlayerController;
	AGameModeBattle();

	void OnFailure();

	void AddCoin(const float Value);

protected:
};
