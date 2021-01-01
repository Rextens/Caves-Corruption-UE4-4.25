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
	//FString xxx = (*setItem)->itemName.ToString();

	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %s"), *xxx));
}

void ABioProgrammator::setItemPointer(UItemSlot *itemSlotReference)
{
	setItems.Add(&itemSlotReference->slotItemReference);
	itemSlotReference->slotID = setItems.Num() - 1;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %i"), saveItems.Num()));
	if (itemSlotReference->slotID <= saveItems.Num() - 1)
	{
		if (saveItems[itemSlotReference->slotID] != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals")));
			itemSlotReference->slotItemReference = saveItems[itemSlotReference->slotID];
		}
	}
}

TArray<UItem*> ABioProgrammator::getItems_Implementation()
{
	return saveItems;
}

FItemSlotSaveStructArray ABioProgrammator::getItemsAsStruct_Implementation()
{
	FItemSlotSaveStructArray tempArray;
	for (int i = 0; i < saveItems.Num(); ++i)
	{
		FItemSlotSaveStruct temp;
		temp.itemName = saveItems[i]->itemName;
		temp.placedItemClass = saveItems[i]->placedItemClass;
		temp.stackable = saveItems[i]->stackable;
		if (saveItems[i]->stackable)
		{
			UStackableItem* stackableItem = Cast<UStackableItem>(saveItems[i]);
			temp.stack = stackableItem->stack;
		}
		tempArray.itemSlots.Add(temp);
	}

	return tempArray;
}

void ABioProgrammator::setItemsArray_Implementation(UPARAM(ref) TArray<UItem*> &items)
{
	saveItems = items;
}

void ABioProgrammator::saveData()
{
	for (int i = 0; i < setItems.Num(); ++i)
	{
		if (saveItems.Num() - 1 < i)
		{
			if (saveItems.Num() < setItems.Num())
			{
				saveItems.Add(nullptr);
			}
			saveItems[i] = *setItems[i];
		}
		else if (setItems[i] != nullptr)
		{
			saveItems[i] = *setItems[i];
		}
	}
	setItems.Empty();
}