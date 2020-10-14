// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemRepresentation.h"
#include "PlacedRock.h"

UItemRepresentation::UItemRepresentation(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UItemRepresentation::createItem()
{
	item = NewObject<UItem>();
	//item->placedItemClass = APlacedRock::StaticClass();
}
