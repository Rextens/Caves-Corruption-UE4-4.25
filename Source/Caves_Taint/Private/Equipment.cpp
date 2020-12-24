// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

UStackableItem* UEquipment::getStackableReferenceInstead(UItem* item)
{
	return Cast<UStackableItem>(item); 
}

void UEquipment::addItemToDisplay_Implementation(const TArray<UItem*>& VarName)
{

}

void UEquipment::updateDisplay_Implementation()
{

}

void UEquipment::onClose()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Couldn't load"));
}