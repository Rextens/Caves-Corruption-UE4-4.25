 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Item.h"
#include "VoxelTools/Gen/VoxelSphereTools.h"
#include "VoxelTools/VoxelDataTools.h"
#include "VoxelData/VoxelData.h"
#include "BioProgrammator.h"
#include "StackableItem.h"
#include "Equipment.h"
#include "UsableItem.h"
#include <map>
#include "chunkBox.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CAVES_TAINT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& objectInitializer);

protected: 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Main function 
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	//My variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isGuiOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool showHUD = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool showItemStats = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerController *playerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent *characterView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		USkeletalMesh* skeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = SkeletalMesh)
		USkeletalMeshComponent* characterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UItem*> itemsInEquipment;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//TArray<UItem*> itemsInToolBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString currentWorldName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItem* leftHand = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItem* rightHand = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 selectedItem = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UUIBase*> currentlyOpenUIs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isItemDraggableGuiOpen = false;
	//My function 

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();

	UFUNCTION()
		void turnVertical(float value);

	UFUNCTION()
		void turnHorizontal(float value);

	UFUNCTION()
		void action();

	UFUNCTION()
		void placeItem();

	UFUNCTION()
		void materialsInSphere(TArray<FModifiedVoxelValue> &modifiedValues, AVoxelWorld* voxelWorldReference);

	UFUNCTION()
		int32 isInTheInventory(FName itemID);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItem* dragItem;

	UFUNCTION(BlueprintCallable)
		void addItemToEquipment(FName objectID, UClass* objectClass, bool stackable, bool splitStack = false, int32 stackAmount = 1)
		{
			if (stackable)
			{
				UStackableItem* stackableItem = NewObject<UStackableItem>();

				stackableItem->itemName = objectID;
				stackableItem->placedItemClass = objectClass;

				int32 equipmentIndex = isInTheInventory(stackableItem->itemName);

				if (equipmentIndex == -1 || splitStack)
				{
					stackableItem->stack = stackAmount;
					itemsInEquipment.Add(stackableItem);
					itemsInEquipment[itemsInEquipment.Num() - 1]->equipmentIndex = itemsInEquipment.Num() - 1;
				}
				else
				{
					Cast<UStackableItem>(itemsInEquipment[equipmentIndex])->stack += 1;
				}
			}
			else
			{
				UItem* createdItem = NewObject<UItem>();

				createdItem->itemName = objectID;
				createdItem->placedItemClass = objectClass;

				itemsInEquipment.Add(createdItem);
				itemsInEquipment[itemsInEquipment.Num() - 1]->equipmentIndex = itemsInEquipment.Num() - 1;
			}
		}

	UFUNCTION(BlueprintCallable)
		void addItemReferenceToEquipment(UItem* itemReference);
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//	TSubclassOf<UEquipment> equipmentClassReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UEquipment *equipment;

	//UFUNCTION(BlueprintCallable)
	//	void addItemReferenceToEquipment();

	UFUNCTION(BlueprintCallable)
		void insertItemToEquipment(FName objectID, UClass* objectClass, bool stackable, int32 index, int32 stack);

	UFUNCTION(BlueprintCallable)
		void insertItemReferenceToEquipment(UItem *itemReference, int32 index);

//	UFUNCTION(BlueprintCallable)
//		void removeItemFromEquipment(UItem* itemReference, bool removeWholeStack = false, int32 removeMoreThanOneItem = 1);

	UFUNCTION(BlueprintCallable)
		void removeItemFromEquipment(int32 index, bool removeWholeStack = false, int32 removeMoreThanOneItem = 1);

	UFUNCTION(BlueprintCallable)
		void checkItemToRemove(int32 index);

	UFUNCTION(BlueprintCallable)
		void updateItemIndexes();

	UFUNCTION(BlueprintCallable)
		void saveCube(FVector cubeLocation);

	UFUNCTION(BlueprintCallable)
		FVector getPlayerCube();

	UFUNCTION(BlueprintCallable)
		void spawnStartingChunkCubes();

	UFUNCTION(BlueprintCallable)
		void checkChunks();

	UFUNCTION(BlueprintCallable)
		void removeChunks();

	UFUNCTION(BlueprintCallable)
		int32 findChunk(FVector position);

	TArray<AchunkBox*> chunks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector lastChunk;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 renderRadius = 1;
};
