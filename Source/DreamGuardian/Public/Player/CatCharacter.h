// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CatCharacter.generated.h"

UCLASS(Blueprintable)
class ACatCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	float MaxValueHealth{100.f};
	UPROPERTY(EditDefaultsOnly, Category = Cat)
	float MaxValueEnergy{100.f};

private:
	UPROPERTY(VisibleAnywhere, Category = Cat)
	float ValueHealth{100.f};
	UPROPERTY(VisibleAnywhere, Category = Cat)
	float ValueEnergy{100.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	ACatCharacter();
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	virtual void BeginPlay() override;
};
