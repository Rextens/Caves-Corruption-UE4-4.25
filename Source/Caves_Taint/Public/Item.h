// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlacedRock.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* placedItemClass;
};
