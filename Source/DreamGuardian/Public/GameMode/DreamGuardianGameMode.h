// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DreamGuardianGameMode.generated.h"

UCLASS(minimalapi)
class ADreamGuardianGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Level Defaults 关卡默认值")
	float SweetDreamValue{100.f};
	UPROPERTY(EditAnywhere, Category = "Level Defaults 关卡默认值")
	float QuietValue{100.f};

public:
	ADreamGuardianGameMode();

protected:
};



