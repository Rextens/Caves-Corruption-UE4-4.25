// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgrammerInterface.h"

void UProgrammerInterface::onStart()
{
	testItem = NewObject<UItem>();
	testItem->itemName = "fdsdsads1231231";
}

void UProgrammerInterface::initElements_Implementation()
{

}

void UProgrammerInterface::saveItem_Implementation()
{

}


void UProgrammerInterface::onClose()
{
	saveItem();
}