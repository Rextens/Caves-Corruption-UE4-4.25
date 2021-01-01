// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Item.h"
#include "SaveChunk.h"
#include "ItemHolder.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UItemHolder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAVES_TAINT_API IItemHolder
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		TArray<UItem*> getItems();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		FItemSlotSaveStructArray getItemsAsStruct();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void setItemsArray(UPARAM(ref) TArray<UItem*> &items);
};
