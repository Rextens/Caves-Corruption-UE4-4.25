// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveWorld.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CAVES_TAINT_API USaveWorld : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic)
		int32 seed;
};
