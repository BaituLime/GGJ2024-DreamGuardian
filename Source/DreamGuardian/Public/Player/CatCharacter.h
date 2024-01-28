// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CatCharacter.generated.h"

class AEnemy;

UCLASS(Blueprintable)
class ACatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	friend class ACatPlayerController;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	float MaxValueHealth{100.f};
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	float ValueAttack{30.f};
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	float ScopeAttack{100.f};

private:
	UPROPERTY(VisibleAnywhere, Category = Cat)
	float ValueHealth{100.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY()
	ACatPlayerController* CatPlayerController;

public:
	ACatCharacter();
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable)
	void DecreaseHealthValue(const float Value);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Attack(AEnemy* Enemy);

protected:
	virtual void BeginPlay() override;

private:
	void OnFailure();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetAttackValue() const { return ValueAttack; }
};
