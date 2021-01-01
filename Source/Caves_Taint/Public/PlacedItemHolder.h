// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlacedItem.h"
#include "Item.h"
#include "PlacedItemHolder.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API APlacedItemHolder : public APlacedItem
{
	GENERATED_BODY()
public:
	TArray<UItem**> setItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UItem*> saveItems;
};
