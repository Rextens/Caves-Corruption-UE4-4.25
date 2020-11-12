// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemRepresentation.h"
#include "PlacedRock.h"

UItemRepresentation::UItemRepresentation(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UItemRepresentation::addItemToToolbar()
{
	/*
	APlayerCharacter* characterReference = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	for (int i = 0; i < 9; ++i)
	{
		if (characterReference->itemsInToolBar[i] == nullptr)
		{
			characterReference->itemsInToolBar[i] = this->item;

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));

			

			break;
		}
	}
	*/
}