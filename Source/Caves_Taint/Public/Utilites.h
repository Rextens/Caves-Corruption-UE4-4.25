// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/UObjectGlobals.h"
#include "Item.h"
#include "Utilites.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API UUtilites : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
		static UObject* duplicateObject(UObject* reference, UObject* owner);

	UFUNCTION(BlueprintCallable)
		static void swapItemPointers(UItem* firstItem, UItem* secondItem);
};
