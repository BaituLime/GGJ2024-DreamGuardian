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
#include "Components/WidgetComponent.h"
#include "DreamGuardian/PrintString.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameMode/GameModeBattle.h"
#include "GameMode/Human.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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

	CatDistance = FVector::Distance(Cat->GetActorLocation(), Human->GetActorLocation());
	AwakeTimes = .5f + 1.5f / (1 + (CatDistance / 80.f));
	if (AwakeTimes > 1.5f && GameModeBattle->ValueCoin > 0 && CatActionState <= ECAS_Chasing)
	{
		WidgetGeneral->OpenTips();
		if (bIsFPressed)
		{
			GameModeBattle->ValueCoin -= .2f * DeltaSeconds;
			Human->ValueSweetDream += 2.f * DeltaSeconds;
		}
	}
	else
	{
		WidgetGeneral->CloseTips();
	}

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
			CatAttackMethod = ECAM_Normal;
			StopMovement();
		}
		break;
	case ECAS_ConfirmToAttack:
		if (CatAttackMethod == ECAM_W)
		{
			FHitResult Hit;
			bool bHitSuccessful = false;
			if (bIsTouch)
			{
				bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true,
				                                         Hit);
			}
			else
			{
				bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
			}

			if (bHitSuccessful)
			{
				FRotator Rotator = Cat->GetActorRotation();
				Cat->SetActorRotation(FRotator{
					Rotator.Pitch, UKismetMathLibrary::MakeRotFromX(Hit.ImpactPoint - Cat->GetActorLocation()).Yaw,
					Rotator.Roll
				});
			}
		}
		break;
	case ECAS_ReadyToAttack:
		if (CatAttackMethod == ECAM_Normal)
		{
			CatActionState = ECAS_Attacking;
			StopMovement();
			Cat->CachedEnemy = CachedEnemy;
			Cat->GetMesh()->GetAnimInstance()->Montage_Play(Cat->MontageAttack);
		}
		else if (CatAttackMethod == ECAM_Q)
		{
			if (!UKismetSystemLibrary::IsValid(CachedEnemy))
			{
				CatActionState = ECAS_Nothing;
				StopMovement();
				Cat->GetCharacterMovement()->MaxWalkSpeed = 800.f;
				break;
			}
			if (FVector::Distance(Cat->GetActorLocation(), CachedEnemy->GetActorLocation()) <= Cat->ScopeAttack)
			{
				CatActionState = ECAS_Attacking;
				StopMovement();
				Cat->GetCharacterMovement()->MaxWalkSpeed = 800.f;
				Cat->CachedEnemy = CachedEnemy;
				Human->DecreaseQuietValue(10.f * AwakeTimes);
				Cat->GetMesh()->GetAnimInstance()->Montage_Play(Cat->MontageQ);
			}
		}
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
	Human = Cast<AHuman>(UGameplayStatics::GetActorOfClass(GetWorld(), AHuman::StaticClass()));

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

		EnhancedInputComponent->BindAction(QClickAction, ETriggerEvent::Started, this,
		                                   &ACatPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(QClickAction, ETriggerEvent::Triggered, this,
		                                   &ACatPlayerController::OnQTriggered);
		EnhancedInputComponent->BindAction(QClickAction, ETriggerEvent::Completed, this,
		                                   &ACatPlayerController::OnQReleased);
		EnhancedInputComponent->BindAction(QClickAction, ETriggerEvent::Canceled, this,
		                                   &ACatPlayerController::OnQReleased);

		EnhancedInputComponent->BindAction(WClickAction, ETriggerEvent::Started, this,
		                                   &ACatPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(WClickAction, ETriggerEvent::Triggered, this,
		                                   &ACatPlayerController::OnWTriggered);
		EnhancedInputComponent->BindAction(WClickAction, ETriggerEvent::Completed, this,
		                                   &ACatPlayerController::OnWReleased);
		EnhancedInputComponent->BindAction(WClickAction, ETriggerEvent::Canceled, this,
		                                   &ACatPlayerController::OnWReleased);

		EnhancedInputComponent->BindAction(EClickAction, ETriggerEvent::Started, this,
		                                   &ACatPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(EClickAction, ETriggerEvent::Triggered, this,
		                                   &ACatPlayerController::OnETriggered);
		EnhancedInputComponent->BindAction(EClickAction, ETriggerEvent::Completed, this,
		                                   &ACatPlayerController::OnEReleased);
		EnhancedInputComponent->BindAction(EClickAction, ETriggerEvent::Canceled, this,
		                                   &ACatPlayerController::OnEReleased);

		EnhancedInputComponent->BindAction(RClickAction, ETriggerEvent::Started, this,
		                                   &ACatPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(RClickAction, ETriggerEvent::Triggered, this,
		                                   &ACatPlayerController::OnRTriggered);
		EnhancedInputComponent->BindAction(RClickAction, ETriggerEvent::Completed, this,
		                                   &ACatPlayerController::OnRReleased);
		EnhancedInputComponent->BindAction(RClickAction, ETriggerEvent::Canceled, this,
		                                   &ACatPlayerController::OnRReleased);

		EnhancedInputComponent->BindAction(FClickAction, ETriggerEvent::Triggered, this,
		                                   &ACatPlayerController::OnFTriggered);
		EnhancedInputComponent->BindAction(FClickAction, ETriggerEvent::Completed, this,
		                                   &ACatPlayerController::OnFReleased);
		EnhancedInputComponent->BindAction(FClickAction, ETriggerEvent::Canceled, this,
		                                   &ACatPlayerController::OnRReleased);
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
	if (Human->bIsDead || CatActionState >= ECAS_ConfirmToAttack)
		return;
	CatActionState = ECAS_Nothing;
	StopMovement();
	bIsFPressed = false;
}

// Triggered every frame when the input is held down
void ACatPlayerController::OnSetDestinationTriggered()
{
	if (Human->bIsDead || CatActionState >= ECAS_ConfirmToAttack)
		return;
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
			WidgetGeneral->DisplaySkill(4);
		}
		else
		{
			// Move.
			CatActionState = ECAS_Moving;
			CachedDestination = Hit.Location;
			WidgetGeneral->DisplaySkill(10);
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
	if (CatActionState != ECAS_ConfirmToAttack)
		return;

	if (CatAttackMethod == ECAM_Q)
	{
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

		if (bHitSuccessful)
		{
			CachedEnemy = Cast<AEnemy>(Hit.GetActor());
			if (CachedEnemy)
			{
				CatActionState = ECAS_ReadyToAttack;
				Cat->GetCharacterMovement()->MaxWalkSpeed = 5600.f;
				UAIBlueprintHelperLibrary::SimpleMoveToActor(this, CachedEnemy);
			}
		}
	}
	else if (CatAttackMethod == ECAM_W)
	{
		CatActionState = ECAS_Attacking;
		Human->DecreaseQuietValue(20.f * AwakeTimes);
		Cat->GetMesh()->GetAnimInstance()->Montage_Play(Cat->MontageW);
	}
	else if (CatAttackMethod == ECAM_E)
	{
		CatActionState = ECAS_Attacking;
		Human->DecreaseQuietValue(40.f * AwakeTimes);
		Cat->GetMesh()->GetAnimInstance()->Montage_Play(Cat->MontageE);
	}
	else if (CatAttackMethod == ECAM_R)
	{
		CatActionState = ECAS_Attacking;
		Human->DecreaseQuietValue(60.f * AwakeTimes);
		Cat->GetMesh()->GetAnimInstance()->Montage_Play(Cat->MontageR);
	}
}

void ACatPlayerController::OnConfirmReleased()
{
}

void ACatPlayerController::OnQTriggered()
{
	if (Human->bIsDead || CatActionState >= ECAS_ConfirmToAttack)
		return;
	WidgetGeneral->DisplaySkill(0);
	CatActionState = ECAS_ConfirmToAttack;
	CatAttackMethod = ECAM_Q;
}

void ACatPlayerController::OnQReleased()
{
	if (CatActionState == ECAS_ConfirmToAttack)
	{
		WidgetGeneral->DisplaySkill(10);
		CatActionState = ECAS_Nothing;
	}
}

void ACatPlayerController::OnWTriggered()
{
	if (Human->bIsDead || CatActionState >= ECAS_ConfirmToAttack)
		return;
	WidgetGeneral->DisplaySkill(1);
	CatActionState = ECAS_ConfirmToAttack;
	CatAttackMethod = ECAM_W;
	Cat->WidgetComponentLightScope->SetVisibility(true);
}

void ACatPlayerController::OnWReleased()
{
	if (CatActionState == ECAS_ConfirmToAttack)
	{
		WidgetGeneral->DisplaySkill(10);
		CatActionState = ECAS_Nothing;
		Cat->WidgetComponentLightScope->SetVisibility(false);
	}
}

void ACatPlayerController::OnETriggered()
{
	if (Human->bIsDead || CatActionState >= ECAS_ConfirmToAttack)
		return;
	WidgetGeneral->DisplaySkill(2);
	CatActionState = ECAS_ConfirmToAttack;
	CatAttackMethod = ECAM_E;
}

void ACatPlayerController::OnEReleased()
{
	if (CatActionState == ECAS_ConfirmToAttack)
	{
		WidgetGeneral->DisplaySkill(10);
		CatActionState = ECAS_Nothing;
	}
}

void ACatPlayerController::OnRTriggered()
{
	if (Human->bIsDead || CatActionState >= ECAS_ConfirmToAttack)
		return;
	WidgetGeneral->DisplaySkill(3);
	CatActionState = ECAS_ConfirmToAttack;
	CatAttackMethod = ECAM_R;
}

void ACatPlayerController::OnRReleased()
{
	if (CatActionState == ECAS_ConfirmToAttack)
	{
		WidgetGeneral->DisplaySkill(10);
		CatActionState = ECAS_Nothing;
	}
}

void ACatPlayerController::OnFTriggered()
{
	bIsFPressed = true;
}

void ACatPlayerController::OnFReleased()
{
	bIsFPressed = false;
}

void ACatPlayerController::ReturnToNothing()
{
	Cat->WidgetComponentLightScope->SetVisibility(false);
	WidgetGeneral->DisplaySkill(10);
	CatActionState = ECAS_Nothing;
}
