// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ItemHolder.h"
#include "SaveChunk.h"
#include "PlacedItemHolder.h"
#include "chunkBox.generated.h"

UCLASS(BlueprintType)
class CAVES_TAINT_API AchunkBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AchunkBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* collisionBox;

	void onSpawned();

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void DestroyChunk();

	UFUNCTION()
		FItemSlotSaveStruct convertItemToItemStruct(UItem *item);

	UFUNCTION()
		UItem* convertItemStructToItem(FItemSlotSaveStruct itemStruct);
};
