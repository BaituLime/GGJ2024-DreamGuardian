// Copyright Baitulime. All Rights Reserved.


#include "Others/Coin.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameMode/GameModeBattle.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CatCharacter.h"
#include "Player/CatPlayerController.h"


ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetSphereRadius(24.f);
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundAppear, GetActorLocation());
}

void ACoin::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ACatCharacter* CatCharacter = Cast<ACatCharacter>(OtherActor);
	ACatPlayerController* CatPlayerController = Cast<ACatPlayerController>(CatCharacter->GetController());
	AGameModeBattle* GameModeBattle = Cast<AGameModeBattle>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CatCharacter && CatPlayerController && GameModeBattle)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SoundPick);
		GameModeBattle->AddCoin(1);
		CatPlayerController->UpdateCoinNumber();
		Destroy();
	}
}
