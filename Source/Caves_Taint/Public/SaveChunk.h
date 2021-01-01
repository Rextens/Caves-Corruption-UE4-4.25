// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveChunk.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlacedItemSaveStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* placedItemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector location;
};

USTRUCT(BlueprintType)
struct FItemSlotSaveStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName itemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* placedItemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool stackable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 stack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 index;
};

USTRUCT(BlueprintType)
struct FItemSlotSaveStructArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FItemSlotSaveStruct> itemSlots;
};

UCLASS()
class CAVES_TAINT_API USaveChunk : public USaveGame
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
		TArray<FPlacedItemSaveStruct> placedItems;
	
	UPROPERTY()
		TArray<FItemSlotSaveStructArray> itemSlots;
};
