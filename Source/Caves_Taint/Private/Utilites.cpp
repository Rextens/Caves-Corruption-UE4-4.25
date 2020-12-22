// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilites.h"

UObject* UUtilites::duplicateObject(UObject* reference, UObject *owner)
{
	return DuplicateObject<UObject>(reference, owner);
}

void UUtilites::swapItemPointers(UItem* firstItem, UItem* secondItem)
{
	//UItem* temp = DuplicateObject<UItem>(firstItem, owner);
	firstItem->itemName = "fnsjfbdshjfbds";
	secondItem = firstItem;
	//secondItem = temp;
}