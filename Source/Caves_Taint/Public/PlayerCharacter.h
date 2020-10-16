 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Item.h"
#include "ShatteredStone.h"
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
		APlayerController *playerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent *characterView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		USkeletalMesh* skeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = SkeletalMesh)
		USkeletalMeshComponent* characterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UItem*> itemsInEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UItem*> itemsInToolBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItem* leftHand = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItem* rightHand = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 selectedItem = 0;

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
		void turnMouseWheel(float value);

	UFUNCTION()
		void openEquipment();

	UFUNCTION()
		void hideHUD();

	UFUNCTION()
		void action();

	UFUNCTION()
		void placeItem();

		int32 isInTheInventory(FName itemID);
		int32 isInTheToolBar(FName itemID);

		template<class ItemClass> void addItemToEquipment()
		{
			ItemClass* createdItem = NewObject<ItemClass>();

			UStackableItem* stackable = Cast<UStackableItem>(createdItem);

			if (stackable)
			{
				int32 toolBarIndex = isInTheToolBar(stackable->itemName);

				if (toolBarIndex == -1)
				{
					int32 equipmentIndex = isInTheInventory(stackable->itemName);

					if (equipmentIndex == -1)
					{
						itemsInEquipment.Add(stackable);
					}
					else
					{
						Cast<UStackableItem>(itemsInEquipment[equipmentIndex])->stack += 1;
					}
				}
				else
				{
					Cast<UStackableItem>(itemsInToolBar[toolBarIndex])->stack += 1;
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not stackable"));
			}
		}
};
