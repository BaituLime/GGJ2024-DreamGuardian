// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UBehaviorTree;

UCLASS()
class DREAMGUARDIAN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = Enemy)
	float MaxValueHealth{100.f};
	UPROPERTY(EditDefaultsOnly, Category = Enemy)
	float SpeedMoving{100.f};
	UPROPERTY(EditDefaultsOnly, Category = Enemy)
	float ValueAttack{5.f};
	UPROPERTY(EditDefaultsOnly, Category = Enemy)
	float ScopeAttack{100.f};

	UPROPERTY(EditAnywhere, Category = Enemy)
	UBehaviorTree* BehaviorTree{nullptr};
	UPROPERTY(EditAnywhere, Category = Enemy)
	TSubclassOf<AActor> CoinType;

private:
	UPROPERTY(VisibleAnywhere, Category = Enemy)
	float ValueHealth;

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	                       FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Attack(AActor* TargetActor);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ActualAttack(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void DecreaseHealthValue(const float Value);

public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetAttackScope() const { return ScopeAttack; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetAttackValue() const { return ValueAttack; }
};
