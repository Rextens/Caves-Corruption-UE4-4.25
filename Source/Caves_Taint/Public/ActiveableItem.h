// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlacedItem.h"
#include "ActiveableItem.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API AActiveableItem : public APlacedItem
{
	GENERATED_BODY()
public:
	virtual void activation() {};
};
