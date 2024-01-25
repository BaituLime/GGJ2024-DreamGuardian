// Copyright Baitulime. All Rights Reserved.

#include "GameMode/DreamGuardianGameMode.h"
#include "Player/CatPlayerController.h"
#include "Player/CatCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADreamGuardianGameMode::ADreamGuardianGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACatPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}