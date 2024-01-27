// Copyright Baitulime. All Rights Reserved.


#include "Player/EnemyController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameMode/Human.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Prediction.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Touch.h"
#include "Player/CatCharacter.h"
#include "Player/Enemy.h"
#include "Traps/TrapMolarRod.h"

AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;

	AiPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	AiPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);

	GetBlackboardComponent()->SetValueAsObject(
		TEXT("HumanActor"), UGameplayStatics::GetActorOfClass(GetWorld(), AHuman::StaticClass()));
	ControlledEnemy = Cast<AEnemy>(GetPawn());
	RunBehaviorTree(ControlledEnemy->GetBehaviorTree());
}

void AEnemyController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) == UAISense_Sight::StaticClass())
	{
		// Handle Sight Sense.
		if (Actor->IsA(ATrapMolarRod::StaticClass()) || Actor->IsA(ACatCharacter::StaticClass()))
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Actor);
			}
			else
			{
				GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
				UAISense_Prediction::RequestPawnPredictionEvent(GetPawn(), Actor, PredictionTime);
				GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), Stimulus.StimulusLocation);
			}
		}
	}
	else if (UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) == UAISense_Hearing::StaticClass())
	{
		// Handle Hearing Sense.
		if (Stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), Stimulus.StimulusLocation);
		}
	}
	else if (UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) == UAISense_Touch::StaticClass())
	{
		// Handle Touch Sense.
		if (Actor->IsA(ATrapMolarRod::StaticClass()) || Actor->IsA(ACatCharacter::StaticClass()))
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Actor);
			}
			else
			{
				GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
				GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), Stimulus.StimulusLocation);
			}
		}
	}
	else if (UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) == UAISense_Prediction::StaticClass())
	{
		// Handle Prediction Sense.
		if (Stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), Stimulus.StimulusLocation);
		}
	}
}
