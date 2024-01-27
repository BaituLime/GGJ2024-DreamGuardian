// Copyright Baitulime. All Rights Reserved.


#include "Player/Enemy.h"

#include "NiagaraDataInterfaceEmitterBinding.h"
#include "Components/CapsuleComponent.h"
#include "DreamGuardian/PrintString.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AISense_Touch.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	ValueHealth = MaxValueHealth;
	GetCharacterMovement()->MaxWalkSpeed = SpeedMoving;
}

void AEnemy::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
                       FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	UAISense_Touch::ReportTouchEvent(GetWorld(), this, Other, HitLocation);
}

void AEnemy::DecreaseHealthValue(const float Value)
{
	PrintFormat("%s decreases %f Health value.", *GetName(), Value)
	ValueHealth -= Value;
	if (ValueHealth <= 0)
		Destroy();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
