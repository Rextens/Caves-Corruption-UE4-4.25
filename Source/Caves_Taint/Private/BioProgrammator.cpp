// Fill out your copyright notice in the Description page of Project Settings.

#include "BioProgrammator.h"
#include "ProgrammerInterface.h"
#include "StackableItem.h"
#include "PlayerCharacter.h"

ABioProgrammator::ABioProgrammator()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> programmerInterfaceClassFinder(TEXT("/Game/Components/UI/ProgrammerInterface_BP"));
	programmatorClass = programmerInterfaceClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UEquipment> equipmentClassFinder(TEXT("/Game/Components/UI/Equipment_BP"));
	equipmentClass = equipmentClassFinder.Class;
}

void ABioProgrammator::BeginPlay()
{
	Super::BeginPlay();

	//if (settedItem == nullptr)
	//{
	//	settedItem = NewObject<UItem>();
	//	settedItem->itemName = "fgdsujfjdsi";
	//}
}

void ABioProgrammator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (setItem != nullptr)
	{
	//	if(*setItem != NULL)
		//if (*setItem != nullptr)
		//{
		//	FString xxx = (*setItem)->itemName.ToString();
		//}
		//{
		//	
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %s"), *xxx));
		//}
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
	}
	else
	{
		//
	}
}

void ABioProgrammator::activation()
{
	if (programmatorClass != nullptr && equipmentClass != nullptr)
	{
		APlayerCharacter* characterReference = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		programmatorWidget = CreateWidget<UProgrammerInterface>(this->GetGameInstance(), programmatorClass);
		characterReference->equipment = CreateWidget<UEquipment>(this->GetGameInstance(), equipmentClass);
	
		if (programmatorWidget != nullptr && characterReference->equipment != nullptr)
		{
			programmatorWidget->AddToViewport();
			programmatorWidget->programmatorReference = this;
			//setItem = &programmatorWidget->testItem;
			//setItemPointer();
			programmatorWidget->initElements();
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

void ABioProgrammator::printPointer()
{
	FString xxx = (*setItem)->itemName.ToString();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %s"), *xxx));
}

void ABioProgrammator::setItemPointer(UItemSlot *itemSlotReference)
{
	setItem = &itemSlotReference->slotItemReference;

	if (saveItem != nullptr)
	{
		itemSlotReference->slotItemReference = saveItem;
	}
}

void ABioProgrammator::saveData()
{
	if (setItem != nullptr)
	{
		saveItem = *setItem;
	}
}