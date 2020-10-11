// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item.h"
#include "ItemRepresentation.generated.h"

/**
 * 
 */

class X {

};

UCLASS()
class CAVES_TAINT_API UItemRepresentation : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UItemRepresentation(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItem* item;

	UFUNCTION(BlueprintCallable)
		void createItem();
};
