// Copyright Baitulime. All Rights Reserved.


#include "GameMode/Human.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "DreamGuardian/PrintString.h"
#include "GameMode/GameModeBattle.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/WidgetFailure.h"
#include "Widgets/WidgetHuman.h"


AHuman::AHuman()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(BoxComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Overlay"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void AHuman::BeginPlay()
{
	Super::BeginPlay();

	WidgetHuman = Cast<UWidgetHuman>(WidgetComponent->GetWidget());
	WidgetFailure = CreateWidget<UWidgetFailure>(UGameplayStatics::GetPlayerController(GetWorld(), 0),
	                                             WidgetClassFailure);
	WidgetFailure->AddToViewport();
	WidgetFailure->SetVisibility(ESlateVisibility::Collapsed);
}

void AHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ValueAwake = FMath::Clamp(ValueAwake - DeltaTime, 0.f, 100.f);
	WidgetHuman->SetDreamAwake(ValueSweetDream, ValueAwake);
}

void AHuman::DecreaseSweetDreamValue(const float Value)
{
	if (bIsDead)
		return;
	PrintFormat("Human decreases %f SweetDream value.", Value)
	ValueSweetDream -= Value;
	if (ValueSweetDream <= 0)
		OnFailure();
}

void AHuman::DecreaseQuietValue(const float Value)
{
	if (bIsDead)
		return;
	PrintFormat("Human decreases %f quiet value.", Value)
	ValueAwake += Value;
	if (ValueAwake >= 100)
		OnFailure();
}

void AHuman::OnFailure()
{
	Print("AHuman::OnFailure")
	bIsDead = true;
	AGameModeBattle* GameModeBattle = Cast<AGameModeBattle>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeBattle->OnFailure();
	WidgetFailure->SetDreamAwake(ValueSweetDream, ValueAwake);
	WidgetFailure->SetVisibility(ESlateVisibility::Visible);
}
