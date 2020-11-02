// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveableItem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "BioProgrammator.generated.h"

/**
 * 
 */
UCLASS()
class CAVES_TAINT_API ABioProgrammator : public AActiveableItem
{
	GENERATED_BODY()
public:
	ABioProgrammator();

	void activation() override;
	
	UClass* MyWidgetClass;
	UUserWidget* programmatorWidget;
};
