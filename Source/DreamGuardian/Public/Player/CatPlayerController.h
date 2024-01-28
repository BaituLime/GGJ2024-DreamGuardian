// Copyright Baitulime. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "CatPlayerController.generated.h"

class UWidgetGeneral;
class AGameModeBattle;
class AEnemy;
class ACatCharacter;
/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UENUM()
enum ECatActionState
{
	ECAS_Nothing,
	ECAS_Moving,
	ECAS_Chasing,
	ECAS_ReadyToAttack,
	ECAS_Attacking
};

UCLASS()
class ACatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	friend class ACatCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ConfirmClickAction;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Cat)
	TSubclassOf<UUserWidget> WidgetClassGeneral;

private:
	ECatActionState CatActionState{ECAS_Nothing};

	FVector CachedDestination;
	AEnemy* CachedEnemy{nullptr};

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed

	ACatCharacter* Cat{nullptr};
	AGameModeBattle* GameModeBattle{nullptr};

	UPROPERTY()
	UWidgetGeneral* WidgetGeneral;

public:
	ACatPlayerController();
	virtual void Tick(float DeltaSeconds) override;

	void UpdateCoinNumber();

protected:
	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();
	void OnConfirmTriggered();
	void OnConfirmReleased();
};
