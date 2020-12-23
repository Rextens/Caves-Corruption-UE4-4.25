// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"	
#include "PlayerCharacter.h" 
#include "ItemRepresentation.generated.h"

/**
 * 
 */

UCLASS()
class CAVES_TAINT_API UItemRepresentation : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItem* item;
};
