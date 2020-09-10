// Copyright Epic Games, Inc. All Rights Reserved.


#include "Caves_TaintGameModeBase.h"
#include "Public/CharacterController.h"
#include "Public/PlayerCharacter.h"

ACaves_TaintGameModeBase::ACaves_TaintGameModeBase() : AGameMode()
{
	PlayerControllerClass = ACharacterController::StaticClass();
	DefaultPawnClass = APlayerCharacter::StaticClass();
}

void ACaves_TaintGameModeBase::StartPlay() 
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World"));

		
	}
}