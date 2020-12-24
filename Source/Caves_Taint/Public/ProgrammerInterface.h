// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BioProgrammator.h"
#include "Item.h"
#include "UIBase.h"
#include "ProgrammerInterface.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API UProgrammerInterface : public UUIBase
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
		void onStart();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABioProgrammator *programmatorReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItem* testItem;

	UFUNCTION(BlueprintNativeEvent)
		void initElements();
		virtual void initElements_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void saveItem();
		virtual void saveItem_Implementation();

		void onClose() override;
};
