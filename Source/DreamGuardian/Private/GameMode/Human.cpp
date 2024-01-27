// Copyright Baitulime. All Rights Reserved.


#include "GameMode/Human.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DreamGuardian/PrintString.h"
#include "GameMode/GameModeBattle.h"
#include "Kismet/GameplayStatics.h"


AHuman::AHuman()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(BoxComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AHuman::BeginPlay()
{
	Super::BeginPlay();

	
}

void AHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHuman::DecreaseSweetDreamValue(const float Value)
{
	PrintFormat("Human decreases %f SweetDream value.", Value)
	ValueSweetDream -= Value;
	if (ValueSweetDream <= 0)
		OnFailure();
}

void AHuman::DecreaseQuietValue(const float Value)
{
	PrintFormat("Human decreases %f quiet value.", Value)
	ValueQuiet -= Value;
	if (ValueQuiet <= 0)
		OnFailure();
}

void AHuman::OnFailure()
{
	// TODO: AHuman::OnFailure
	Print("AHuman::OnFailure")
	AGameModeBattle* GameModeBattle = Cast<AGameModeBattle>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeBattle->OnFailure();
}
