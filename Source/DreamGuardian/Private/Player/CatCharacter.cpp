// Copyright Baitulime. All Rights Reserved.

#include "Player/CatCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "DreamGuardian/PrintString.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "GameMode/GameModeBattle.h"
#include "Kismet/GameplayStatics.h"

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
}

void ACatCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ValueEnergy = FMath::Clamp(ValueEnergy + DeltaSeconds, 0, MaxValueEnergy);
}

void ACatCharacter::DecreaseHealthValue(const float Value)
{
	PrintFormat("%s decreases %f Health value.", *GetName(),Value)
	ValueHealth -= Value;
	if (ValueHealth <= 0)
	{
		OnFailure();
	}
}

void ACatCharacter::BeginPlay()
{
	Super::BeginPlay();

	ValueHealth = MaxValueHealth;
	ValueEnergy = MaxValueEnergy;
}

void ACatCharacter::OnFailure()
{
	// TODO: ACatCharacter::OnFailure
	Print("ACatCharacter::OnFailure")
	AGameModeBattle* GameModeBattle = Cast<AGameModeBattle>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeBattle->OnFailure();
}
