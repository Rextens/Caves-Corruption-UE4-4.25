// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Caves_TaintGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API ACaves_TaintGameModeBase : public AGameMode
{
	GENERATED_BODY()

protected:
	ACaves_TaintGameModeBase();

	virtual void StartPlay() override;
};
