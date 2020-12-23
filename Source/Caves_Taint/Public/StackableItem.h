// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "StackableItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CAVES_TAINT_API UStackableItem : public UItem
{
	GENERATED_BODY()

public:
	UStackableItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 stack = 0;
};
