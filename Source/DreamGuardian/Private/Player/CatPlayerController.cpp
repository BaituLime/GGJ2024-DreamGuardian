// Copyright Baitulime. All Rights Reserved.

#include "Player/CatPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Player/CatCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "DreamGuardian/PrintString.h"
#include "Engine/LocalPlayer.h"
#include "GameMode/GameModeBattle.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/Enemy.h"
#include "Widgets/WidgetGeneral.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ACatPlayerController::ACatPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ACatPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	switch (CatActionState)
	{
	case ECAS_Moving:
		if (FVector::Distance(Cat->GetActorLocation(), CachedDestination) < 1.f)
		{
			CatActionState = ECAS_Nothing;
		}
		break;
	case ECAS_Chasing:
		if (!UKismetSystemLibrary::IsValid(CachedEnemy))
		{
			OnInputStarted();
			break;
		}
		if (FVector::Distance(Cat->GetActorLocation(), CachedDestination) <= Cat->ScopeAttack * .9f)
		{
			CatActionState = ECAS_ReadyToAttack;
			StopMovement();
		}
		break;
	case ECAS_ReadyToAttack:
		CatActionState = ECAS_Attacking;
		Cat->Attack(CachedEnemy);
		break;
	default: ;
	}
}

void ACatPlayerController::UpdateCoinNumber()
{
	WidgetGeneral->SetDreamCount(GameModeBattle->ValueCoin);
}

void ACatPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	Cat = Cast<ACatCharacter>(GetPawn());
	GameModeBattle = Cast<AGameModeBattle>(UGameplayStatics::GetGameMode(GetWorld()));

	WidgetGeneral = CreateWidget<UWidgetGeneral>(this, WidgetClassGeneral);
	WidgetGeneral->AddToViewport(-1);
}

void ACatPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this,
		                                   &ACatPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this,
		                                   &ACatPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this,
		                                   &ACatPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this,
		                                   &ACatPlayerController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(ConfirmClickAction, ETriggerEvent::Started, this,
		                                   &ACatPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(ConfirmClickAction, ETriggerEvent::Triggered, this,
		                                   &ACatPlayerController::OnConfirmTriggered);
		EnhancedInputComponent->BindAction(ConfirmClickAction, ETriggerEvent::Completed, this,
		                                   &ACatPlayerController::OnConfirmReleased);
		EnhancedInputComponent->BindAction(ConfirmClickAction, ETriggerEvent::Canceled, this,
		                                   &ACatPlayerController::OnConfirmReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this,
		                                   &ACatPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this,
		                                   &ACatPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this,
		                                   &ACatPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this,
		                                   &ACatPlayerController::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void ACatPlayerController::OnInputStarted()
{
	CatActionState = ECAS_Nothing;
	StopMovement();
}

// Triggered every frame when the input is held down
void ACatPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedEnemy = Cast<AEnemy>(Hit.GetActor());
		if (CachedEnemy)
		{
			// Chase or Attack.
			if (FVector::Distance(CachedEnemy->GetActorLocation(), Cat->GetActorLocation()) <= Cat->ScopeAttack)
			{
				CatActionState = ECAS_ReadyToAttack;
			}
			else
			{
				CatActionState = ECAS_Chasing;
			}
		}
		else
		{
			// Move.
			CatActionState = ECAS_Moving;
			CachedDestination = Hit.Location;
		}
	}

	// Move towards mouse pointer or touch
	FVector WorldDirection = (CachedDestination - Cat->GetActorLocation()).GetSafeNormal();
	Cat->AddMovementInput(WorldDirection, 1.0, false);
}

void ACatPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		switch (CatActionState)
		{
		case ECAS_Chasing:
			UAIBlueprintHelperLibrary::SimpleMoveToActor(this, CachedEnemy);
			break;
		case ECAS_Moving:
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator,
			                                               FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None,
			                                               true);
			break;
		}
	}

	FollowTime = 0.f;
}

void ACatPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ACatPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ACatPlayerController::OnConfirmTriggered()
{
}

void ACatPlayerController::OnConfirmReleased()
{
}
