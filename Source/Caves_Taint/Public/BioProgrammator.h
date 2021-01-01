// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveableItem.h"
#include "Blueprint/UserWidget.h"
#include "Item.h"
#include "ItemSlot.h"
#include "ItemHolder.h"
#include "UsableItem.h"
#include "PlacedItemHolder.h"
#include "Kismet/GameplayStatics.h"
#include "BioProgrammator.generated.h"

class UProgrammerInterface;

/**
 * 
 */

UCLASS(BlueprintType)
class CAVES_TAINT_API ABioProgrammator : public APlacedItemHolder, public IUsableItem
{
	GENERATED_BODY()
public:
	ABioProgrammator();

	virtual void BeginPlay() override;

	void activation() override;

	virtual void Tick(float DeltaTime) override;
	
	UClass* programmatorClass;
	UProgrammerInterface* programmatorWidget;

	UClass* equipmentClass;
	UUserWidget* equipmentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString programmerText;

	UFUNCTION(BlueprintCallable)
		void setItemPointer(UItemSlot *itemSlotReference);

	UFUNCTION(BlueprintCallable)
		void printPointer();

	UFUNCTION(BlueprintCallable)
		void saveData();

		TArray<UItem*> getItems_Implementation();

		FItemSlotSaveStructArray getItemsAsStruct_Implementation();

		void setItemsArray_Implementation(UPARAM(ref) TArray<UItem*> &items);
};
