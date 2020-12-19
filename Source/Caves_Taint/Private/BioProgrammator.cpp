// Fill out your copyright notice in the Description page of Project Settings.

#include "BioProgrammator.h"
#include "PlayerCharacter.h"

ABioProgrammator::ABioProgrammator()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> programmerInterfaceClassFinder(TEXT("/Game/Components/UI/ProgrammerInterface_BP"));
	programmatorClass = programmerInterfaceClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UEquipment> equipmentClassFinder(TEXT("/Game/Components/UI/Equipment_BP"));
	equipmentClass = equipmentClassFinder.Class;
}

void ABioProgrammator::activation()
{
	if (programmatorClass != nullptr && equipmentClass != nullptr)
	{
		APlayerCharacter* characterReference = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		programmatorWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), programmatorClass);
		characterReference->equipment = CreateWidget<UEquipment>(this->GetGameInstance(), equipmentClass);
	
		if (programmatorWidget != nullptr && characterReference->equipment != nullptr)
		{
			programmatorWidget->AddToViewport();
			characterReference->equipment->AddToViewport();

			FInputModeUIOnly InputModeData;

			APlayerController* controllerReference = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			
			characterReference->isGuiOpen = true;
			characterReference->currentlyOpenUIs.Add(programmatorWidget);
			characterReference->currentlyOpenUIs.Add(characterReference->equipment);
			characterReference->isItemDraggableGuiOpen = true;
			characterReference->showItemStats = false; 

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
