// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BioProgrammator.h"
#include "ProgrammerInterface.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API UProgrammerInterface : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABioProgrammator *programmatorReference;
};
