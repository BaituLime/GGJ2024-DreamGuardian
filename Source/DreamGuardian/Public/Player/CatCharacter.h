// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CatCharacter.generated.h"

class UNiagaraSystem;
class UWidgetComponent;
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
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	UNiagaraSystem* NiagaraSystemFlash;
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	UAnimMontage* MontageAttack;
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	UAnimMontage* MontageQ;
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	UAnimMontage* MontageW;
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	UAnimMontage* MontageE;
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	UAnimMontage* MontageR;

private:
	UPROPERTY(VisibleAnywhere, Category = Cat)
	float ValueHealth{100.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY()
	ACatPlayerController* CatPlayerController;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponentLightScope;

	AEnemy* CachedEnemy{nullptr};
	
	UPROPERTY()
	FTimerHandle TimerHandle;

public:
	ACatCharacter();
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable)
	void DecreaseHealthValue(const float Value);

	UFUNCTION(BlueprintCallable)
	void AttackNormal();
	UFUNCTION(BlueprintCallable)
	void AttackQ();
	UFUNCTION(BlueprintCallable)
	void AttackW();
	UFUNCTION(BlueprintCallable)
	void AttackE();
	UFUNCTION(BlueprintCallable)
	void AttackR();

protected:
	virtual void BeginPlay() override;

private:
	void OnFailure();
	void Flash();
	
	UFUNCTION()
	void RestoreE();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetAttackValue() const { return ValueAttack; }
};
