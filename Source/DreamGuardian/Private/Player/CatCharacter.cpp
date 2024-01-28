// Copyright Baitulime. All Rights Reserved.

#include "Player/CatCharacter.h"

#include "EngineUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "DreamGuardian/PrintString.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "GameMode/GameModeBattle.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CatPlayerController.h"
#include "Player/Enemy.h"
#include "Player/EnemyController.h"
#include "Widgets/WidgetGeneral.h"

ACatCharacter::ACatCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	WidgetComponentLightScope = CreateDefaultSubobject<UWidgetComponent>(TEXT("LightScope"));
	WidgetComponentLightScope->SetupAttachment(RootComponent);
	WidgetComponentLightScope->SetRelativeLocationAndRotation(FVector{0.f, 0.f, -90.f}, FRotator{90.f, 90.f, 0.f});
}

void ACatCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACatCharacter::DecreaseHealthValue(const float Value)
{
	PrintFormat("%s decreases %f Health value.", *GetName(), Value)
	ValueHealth -= Value;
	CatPlayerController->WidgetGeneral->SetHealthPercent(FMath::Clamp(ValueHealth / MaxValueHealth, 0.f, 1.f));
	if (ValueHealth <= 0)
	{
		OnFailure();
	}
}

void ACatCharacter::AttackNormal()
{
	if (!UKismetSystemLibrary::IsValid(CachedEnemy))
		return;
	PrintFormat("ACatCharacter::AttackNormal, %s, attacks %s", *GetName(), *CachedEnemy->GetName())
	CachedEnemy->DecreaseHealthValue(30.f);
}

void ACatCharacter::AttackQ()
{
	if (!UKismetSystemLibrary::IsValid(CachedEnemy))
		return;
	PrintFormat("ACatCharacter::AttackNormal, %s, attacks %s", *GetName(), *CachedEnemy->GetName())
	CachedEnemy->DecreaseHealthValue(70.f);
}

void ACatCharacter::AttackW()
{
	Print("ACatCharacter::AttackW")
	for (TActorIterator<AEnemy> i(GetWorld()); i; ++i)
	{
		FVector Dir = i->GetActorLocation() - GetActorLocation();
		Dir.Normalize();
		if (GetActorForwardVector().Dot(Dir) <= FMath::Cos(FMath::DegreesToRadians(30.f)))
		{
			i->DecreaseHealthValue(50.f);
		}
	}
}

void ACatCharacter::AttackE()
{
	Print("ACatCharacter::AttackE")
	for (TActorIterator<AEnemyController> i(GetWorld()); i; ++i)
	{
		if (i->GetBlackboardComponent())
		{
			i->GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsRestrict")), true);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::RestoreE, 5.f);
}

void ACatCharacter::AttackR()
{
	Print("ACatCharacter::AttackR")
	Flash();

	for (TActorIterator<AEnemy> i(GetWorld()); i; ++i)
	{
		i->DecreaseHealthValue(1000.f);
	}
}

void ACatCharacter::BeginPlay()
{
	Super::BeginPlay();

	ValueHealth = MaxValueHealth;

	CatPlayerController = Cast<ACatPlayerController>(GetController());
}

void ACatCharacter::OnFailure()
{
	ValueHealth = MaxValueHealth;
	SetActorLocation(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass())->GetActorLocation());
	CatPlayerController->WidgetGeneral->SetHealthPercent(1.f);
}

void ACatCharacter::Flash()
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraSystemFlash, RootComponent, FName(), FVector::ZeroVector,
	                                             FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}

void ACatCharacter::RestoreE()
{
	Print("ACatCharacter::RestoreE")
	for (TActorIterator<AEnemyController> i(GetWorld()); i; ++i)
	{
		if (i->GetBlackboardComponent())
		{
			i->GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsRestrict")), false);
		}
	}
}
