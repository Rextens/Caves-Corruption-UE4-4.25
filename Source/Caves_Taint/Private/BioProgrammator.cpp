// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "BioProgrammator.h"

ABioProgrammator::ABioProgrammator()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> programmerInterfaceClassFinder(TEXT("/Game/Components/UI/ProgrammerInterface_BP"));
	programmatorClass = programmerInterfaceClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> equipmentClassFinder(TEXT("/Game/Components/UI/Equipment_BP"));
	equipmentClass = equipmentClassFinder.Class;
}

void ABioProgrammator::activation()
{
	if (programmatorClass != nullptr && equipmentClass != nullptr)
	{
		programmatorWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), programmatorClass);
		equipmentWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), equipmentClass);
	
		if (programmatorWidget != nullptr && equipmentWidget != nullptr)
		{
			programmatorWidget->AddToViewport();
			equipmentWidget->AddToViewport();

			FInputModeUIOnly InputModeData;

			APlayerController* controllerReference = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			APlayerCharacter* characterReference = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			characterReference->isGuiOpen = true;
			characterReference->currentlyOpenUIs.Add(programmatorWidget);
			characterReference->currentlyOpenUIs.Add(equipmentWidget);
			characterReference->isItemDraggableGuiOpen = true;

			controllerReference->bShowMouseCursor = true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Couldn't load"));
	}
}
