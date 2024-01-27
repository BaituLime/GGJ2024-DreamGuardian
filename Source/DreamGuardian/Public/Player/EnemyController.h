// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class AEnemy;
struct FAIStimulus;

UCLASS()
class DREAMGUARDIAN_API AEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "AI Perception")
	float PredictionTime{1.5f};

private:
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AiPerceptionComponent;
	UPROPERTY()
	AEnemy* ControlledEnemy{nullptr};

public:
	AEnemyController();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
