// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StackableItem.h"
#include "UIBase.h"
#include "Equipment.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API UEquipment : public UUIBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		UStackableItem* getStackableReferenceInstead(UItem *item);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void addItemToDisplay(const TArray<UItem*>& VarName);

		virtual void addItemToDisplay_Implementation(const TArray<UItem*>& VarName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void updateDisplay();

		virtual void updateDisplay_Implementation();

		void onClose() override;
};
