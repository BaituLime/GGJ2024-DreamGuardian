// Copyright Baitulime. All Rights Reserved.


#include "Others/Coin.h"

#include "Components/CapsuleComponent.h"
#include "GameMode/GameModeBattle.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CatCharacter.h"
#include "Player/CatPlayerController.h"


ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetGenerateOverlapEvents(true);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(CapsuleComponent);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACoin::SetCurrentValue(const float Value)
{
	ValueCurrent = Value;
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Effect.
}

void ACoin::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ACatCharacter* CatCharacter = Cast<ACatCharacter>(OtherActor);
	ACatPlayerController* CatPlayerController = Cast<ACatPlayerController>(CatCharacter->GetController());
	AGameModeBattle* GameModeBattle = Cast<AGameModeBattle>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CatCharacter && CatPlayerController && GameModeBattle)
	{
		// TODO: Effect and UI Updating.
		GameModeBattle->AddCoin(ValueCurrent);
	}
}
