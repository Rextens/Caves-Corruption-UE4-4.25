// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItem* slotItemReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 slotID = 0;
};
