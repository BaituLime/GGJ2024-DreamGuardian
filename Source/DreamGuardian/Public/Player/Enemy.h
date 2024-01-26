// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class DREAMGUARDIAN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = Enemy)
	float MaxValueHealth;
	UPROPERTY(EditDefaultsOnly, Category = Enemy)
	float SpeedMoving{100.f};
	UPROPERTY(EditDefaultsOnly, Category = Enemy)
	float ValueAttack{5.f};
	UPROPERTY(EditDefaultsOnly, Category = Enemy)
	float ScopeAttack{100.f};

private:
	UPROPERTY(VisibleAnywhere, Category = Enemy)
	float ValueHealth;

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Attack();
};
