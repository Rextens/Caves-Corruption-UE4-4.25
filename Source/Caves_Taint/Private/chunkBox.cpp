// Fill out your copyright notice in the Description page of Project Settings.


#include "chunkBox.h"
#include "PlacedItem.h"
#include <string>
#include "Containers/UnrealString.h"
#include "PlayerCharacter.h"

// Sets default values
AchunkBox::AchunkBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	collisionBox->SetBoxExtent(FVector(2048.0f, 2048.0f, 2048.0f));
	collisionBox->SetHiddenInGame(false);
	RootComponent = collisionBox;

	collisionBox->OnComponentEndOverlap.AddDynamic(this, &AchunkBox::OnOverlapEnd);
	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &AchunkBox::OnBeginOverlap);

}

// Called when the game starts or when spawned
void AchunkBox::BeginPlay()
{
	Super::BeginPlay();
}

void AchunkBox::onSpawned()
{
	APlayerCharacter* characterReference = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FString savePath = characterReference->currentWorldName + "/chunks/" + "chunk_" + FString::FromInt(floor(GetActorLocation().X / 4096.0f)) + "_" +
		FString::FromInt(floor(GetActorLocation().Y / 4096.0f)) + "_" +
		FString::FromInt(floor(GetActorLocation().Z / 4096.0f));

	USaveChunk* saveChunkInstance = Cast<USaveChunk>(UGameplayStatics::CreateSaveGameObject(USaveChunk::StaticClass()));
	saveChunkInstance = Cast<USaveChunk>(UGameplayStatics::LoadGameFromSlot(savePath, 0));
	if (saveChunkInstance)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Num: %i"), saveChunkInstance->placedItems.Num()));
		for (int i = 0; i < saveChunkInstance->placedItems.Num(); ++i)
		{
			FActorSpawnParameters SpawnInfo;
			APlacedItem *temp = GetWorld()->SpawnActor<APlacedItem>(saveChunkInstance->placedItems[i].placedItemClass, saveChunkInstance->placedItems[i].location, FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
			
			APlacedItemHolder* itemsSlots = Cast<APlacedItemHolder>(temp);
			if (itemsSlots)
			{
				for (int j = 0; j < saveChunkInstance->itemSlots[i].itemSlots.Num(); ++j)
				{
					if (saveChunkInstance->itemSlots[i].itemSlots[j].index > itemsSlots->saveItems.Num())
					{
						GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, FString::FromInt(saveChunkInstance->itemSlots[i].itemSlots[j].index));
						while(saveChunkInstance->itemSlots[i].itemSlots[j].index > itemsSlots->saveItems.Num())
						{
							itemsSlots->saveItems.Add(nullptr);
						}
					}					
					itemsSlots->saveItems.Add(convertItemStructToItem(saveChunkInstance->itemSlots[i].itemSlots[j]));
				}
			}
		}
	}
}

// Called every frame
void AchunkBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AchunkBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AchunkBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AchunkBox::DestroyChunk()
{
	TArray<AActor*> actorsInChunk;
	collisionBox->GetOverlappingActors(actorsInChunk, APlacedItem::StaticClass());
	USaveChunk* saveChunkInstance = Cast<USaveChunk>(UGameplayStatics::CreateSaveGameObject(USaveChunk::StaticClass()));


	for (int i = 0; i < actorsInChunk.Num(); ++i)
	{
		FPlacedItemSaveStruct placedItem;
		placedItem.placedItemClass = actorsInChunk[i]->GetClass();
		placedItem.location = actorsInChunk[i]->GetActorLocation();
		saveChunkInstance->placedItems.Add(placedItem);

		FItemSlotSaveStructArray itemsArray;
		APlacedItemHolder* itemsSlots = Cast<APlacedItemHolder>(actorsInChunk[i]);
		if (itemsSlots)
		{
			for (int j = 0; j < itemsSlots->saveItems.Num(); ++j)
			{
				if (itemsSlots->saveItems[j] != nullptr)
				{
					FItemSlotSaveStruct tempItemStruct = convertItemToItemStruct(itemsSlots->saveItems[j]);
					tempItemStruct.index = j;
					
					itemsArray.itemSlots.Add(tempItemStruct);
				}
			}
		}
		saveChunkInstance->itemSlots.Add(itemsArray);
	}

	if (actorsInChunk.Num() > 0)
	{
		
		APlayerCharacter* characterReference = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		FString savePath = characterReference->currentWorldName + "/chunks/" + "chunk_" + FString::FromInt(floor(GetActorLocation().X / 4096.0f)) + "_" +
			FString::FromInt(floor(GetActorLocation().Y / 4096.0f)) + "_" +
			FString::FromInt(floor(GetActorLocation().Z / 4096.0f));

		UGameplayStatics::SaveGameToSlot(saveChunkInstance, savePath, 0);
	}
	else
	{
		APlayerCharacter* characterReference = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		FString savePath = characterReference->currentWorldName + "/chunks/" + "chunk_" + FString::FromInt(floor(GetActorLocation().X / 4096.0f)) + "_" +
			FString::FromInt(floor(GetActorLocation().Y / 4096.0f)) + "_" +
			FString::FromInt(floor(GetActorLocation().Z / 4096.0f));

		UGameplayStatics::DeleteGameInSlot(savePath, 0);
	}

	for (int i = 0; i < actorsInChunk.Num(); ++i)
	{
		actorsInChunk[i]->Destroy();
	}

	Destroy();
}

FItemSlotSaveStruct AchunkBox::convertItemToItemStruct(UItem* item)
{
	FItemSlotSaveStruct temp;
	temp.itemName = item->itemName;
	temp.placedItemClass = item->placedItemClass;
	temp.stackable = item->stackable;
	if (item->stackable)
	{
		UStackableItem* stackableItem = Cast<UStackableItem>(item);
		temp.stack = stackableItem->stack;
	}

	return temp;
}

UItem* AchunkBox::convertItemStructToItem(FItemSlotSaveStruct itemStruct)
{
	if (itemStruct.stackable)
	{
		UStackableItem* stackableItem = NewObject<UStackableItem>();
		stackableItem->itemName = itemStruct.itemName;
		stackableItem->placedItemClass = itemStruct.placedItemClass;
		stackableItem->stackable = true;
		stackableItem->stack = itemStruct.stack;
	
		return stackableItem;
	}
	else
	{
		UItem* item = NewObject<UItem>();
		item->itemName = itemStruct.itemName;
		item->placedItemClass = itemStruct.placedItemClass;
		item->stackable = false;

		return item;
	}
}