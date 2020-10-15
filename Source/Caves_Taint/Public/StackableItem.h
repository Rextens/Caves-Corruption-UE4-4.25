// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "StackableItem.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API UStackableItem : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 stack = 0;
};
