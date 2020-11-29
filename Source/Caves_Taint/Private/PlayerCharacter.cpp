// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "UObject/Class.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "VoxelWorldGenerators/VoxelWorldGeneratorHelpers.h"
#include "PlacedRock.h"
#include "CharacterController.h"
#include "VoxelWorld.h"



// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//characterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character's mesh"));
	//characterMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> testMannequin(TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin"));
	//const ConstructorHelpers::FObjectFinder<UAnimationAsset> walkAnimation(TEXT("/Game/AnimStarterPack/Walk_Fwd_Rifle_Ironsights"));



	if (testMannequin.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(testMannequin.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->AddWorldRotation(FRotator(0.0f, 270.0f, 0.0f));

		/*
		if (walkAnimation.Succeeded())
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			//GetMesh()->SetAnimation(walkAnimation.Object);
			//GetMesh()->Play(true);
			GetMesh()->PlayAnimation(walkAnimation.Object, true);
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Loaded"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Could not load animation"));
		}
		*/
		characterView = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
		characterView->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "head");//FName("head"), EAttachLocation::KeepRelativeOffset, true);
		characterView->AddRelativeRotation(FRotator(180.0f, -90.0f, 90.0f));
		characterView->bUsePawnControlRotation = true;
		//bUseControllerRotationPitch = true;
		characterView->bLockToHmd = true;
	}

	//GetMesh()
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	addItemToEquipment("Bioprogrammator", ABioProgrammator::StaticClass(), true, false, 10);
	playerController = Cast<ACharacterController>(GetController());
	
	if (playerController)
	{
		playerController->bEnableClickEvents = true;
		playerController->bEnableMouseOverEvents = true;
	}	

//	for (int i = 0; i < 9; ++i)
//	{
//		itemsInToolBar.Add(nullptr);
//	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::turnHorizontal);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::turnVertical);

	//PlayerInputComponent->BindAxis("ChooseItem", this, &APlayerCharacter::turnMouseWheel);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	//PlayerInputComponent->BindAction("Open/Close Gui", IE_Pressed, this, &APlayerCharacter::openEquipment);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &APlayerCharacter::action);
	PlayerInputComponent->BindAction("Action2", IE_Pressed, this, &APlayerCharacter::placeItem);
}

void APlayerCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();
		
}



void APlayerCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.

	if (!isGuiOpen)
	{
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	if (!isGuiOpen)
	{
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::StartJump()
{
	if (!isGuiOpen)
	{
		bPressedJump = true;
	}
}

void APlayerCharacter::StopJump()
{
	if (!isGuiOpen)
	{
		bPressedJump = false;
	}
}

void APlayerCharacter::turnVertical(float value)
{
	if (!isGuiOpen)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Pitch: %f"), value));
		APlayerCharacter::AddControllerPitchInput(value);
	}
}

void APlayerCharacter::turnHorizontal(float value)
{
	if (!isGuiOpen)
	{
		APlayerCharacter::AddControllerYawInput(value);
	}
}

void APlayerCharacter::materialsInSphere(TArray<FModifiedVoxelValue> &modifiedValues, AVoxelWorld *voxelWorldReference)
{
	for (int i = 0; i < modifiedValues.Num(); ++i) {
		FVoxelMaterial gettedMaterial;
		UVoxelDataTools::GetMaterial(gettedMaterial, voxelWorldReference, modifiedValues[i].Position);
	
		if (gettedMaterial.GetSingleIndex() == 0 || gettedMaterial.GetSingleIndex() == 1) {
			addItemToEquipment("Shattered Stone", nullptr, true, false);
		}
		else if(gettedMaterial.GetSingleIndex() == 2)
		{
			addItemToEquipment("Selfprogrammable Ore", nullptr, true, false);
		}
	}
}

void APlayerCharacter::action()
{
	if (!isGuiOpen)
	{
		FHitResult hitResult;
		GetWorld()->LineTraceSingleByChannel(hitResult, characterView->GetComponentLocation(), characterView->GetForwardVector() * 1000.0f + characterView->GetComponentLocation(), ECC_Visibility);
		DrawDebugLine(GetWorld(), characterView->GetComponentLocation(), characterView->GetForwardVector() * 1000.0f + characterView->GetComponentLocation(), FColor::Red, false, 2.0f);

		AVoxelWorld* voxelWorldReference = nullptr;

		voxelWorldReference = Cast<AVoxelWorld>(hitResult.Actor);

		if (voxelWorldReference != nullptr)
		{			
			TArray<FModifiedVoxelValue> modifiedValues;

			
			UVoxelSphereTools::RemoveSphere(voxelWorldReference, hitResult.Location, 20.0f, &modifiedValues);
			UVoxelSphereTools::SmoothSphere(voxelWorldReference, hitResult.Location, 20.0f, 1.0f);
			materialsInSphere(modifiedValues, voxelWorldReference);
		}
	}
}

void APlayerCharacter::placeItem()
{
	if (selectedItem < itemsInEquipment.Num() && itemsInEquipment[selectedItem] != nullptr)
	{
		if (!isGuiOpen && itemsInEquipment[selectedItem]->placedItemClass != nullptr)
		{
			FHitResult hitResult;
			GetWorld()->LineTraceSingleByChannel(hitResult, characterView->GetComponentLocation(), characterView->GetForwardVector() * 1000.0f + characterView->GetComponentLocation(), ECC_Visibility);
			DrawDebugLine(GetWorld(), characterView->GetComponentLocation(), characterView->GetForwardVector() * 1000.0f + characterView->GetComponentLocation(), FColor::Red, false, 2.0f);

			AActiveableItem* activeable = Cast<AActiveableItem>(hitResult.Actor);

			if (!activeable)
			{
				FRotator Rotation(0.0f, 0.0f, 0.0f);
				FActorSpawnParameters SpawnInfo;

				GetWorld()->SpawnActor<APlacedItem>(itemsInEquipment[selectedItem]->placedItemClass, hitResult.Location, Rotation, SpawnInfo);
				removeItemFromEquipment(itemsInEquipment[selectedItem]->equipmentIndex);
				
			}
			else
			{
				activeable->activation();
			}
		}
	}
}

int32 APlayerCharacter::isInTheInventory(FName itemID)
{
	for (int i = 0; i < itemsInEquipment.Num(); ++i)
	{
		if (itemsInEquipment[i]->itemName == itemID)
		{
			return i;
		}
	}

	return -1;
}
/*
void APlayerCharacter::removeItemFromEquipment(UItem* itemReference, bool removeWholeStack, int32 removeMoreThanOneItem)
{
	if (itemReference->stackable)
	{
		UStackableItem *stackableItemReference = Cast<UStackableItem>(itemReference);
		if (removeWholeStack)
		{
			itemsInEquipment.RemoveAt(itemReference->equipmentIndex);
		}
		else
		{
			stackableItemReference->stack -= removeMoreThanOneItem;

			if (stackableItemReference->stack == 0)
			{
				itemsInEquipment.RemoveAt(stackableItemReference->equipmentIndex);
			}
		}
	}
	else
	{
		itemsInEquipment.RemoveAt(itemReference->equipmentIndex);
	}

	updateItemIndexes();
}
*/

void APlayerCharacter::insertItemToEquipment(FName objectID, UClass* objectClass, bool stackable, int32 index, int32 stack)
{
	if (stackable)
	{
		UStackableItem* stackableItem = NewObject<UStackableItem>();

		stackableItem->itemName = objectID;
		stackableItem->placedItemClass = objectClass;
		stackableItem->stack = stack;

		itemsInEquipment.SetNum(itemsInEquipment.Num() + 1);

		for (int i = itemsInEquipment.Num() - 1; i >= index + 1; --i)
		{
			itemsInEquipment[i] = itemsInEquipment[i - 1];
		}

		itemsInEquipment[index] = stackableItem;
	}
	else
	{
		UItem* createdItem = NewObject<UItem>();
		
		createdItem->itemName = objectID;
		createdItem->placedItemClass = objectClass;

		itemsInEquipment.Add(nullptr);

		for (int i = itemsInEquipment.Num(); i-- > index; )
		{
			itemsInEquipment[i] = itemsInEquipment[i + 1];
		}

		itemsInEquipment[index] = createdItem;
	}
}

void APlayerCharacter::removeItemFromEquipment(int32 index, bool removeWholeStack, int32 removeMoreThanOneItem)
{
	if (itemsInEquipment[index]->stackable)
	{
		if (removeWholeStack)
		{
			itemsInEquipment.RemoveAt(index);
		}
		else
		{
			UStackableItem* stackableItemReference = Cast<UStackableItem>(itemsInEquipment[index]);
			stackableItemReference->stack -= removeMoreThanOneItem;

			if (stackableItemReference->stack == 0)
			{
				itemsInEquipment.RemoveAt(index);
			}
		}
	}
	else
	{
		itemsInEquipment.RemoveAt(index);
	}

	updateItemIndexes();
}

void APlayerCharacter::checkItemToRemove(int32 index)
{
	if (itemsInEquipment[index]->stackable)
	{
		UStackableItem* stackableItemReference = Cast<UStackableItem>(itemsInEquipment[index]);
		if (stackableItemReference->stack == 0)
		{
			itemsInEquipment.RemoveAt(index);
			updateItemIndexes();
		}
	}
}

void APlayerCharacter::updateItemIndexes()
{
	for (int i = 0; i < itemsInEquipment.Num(); ++i)
	{
		itemsInEquipment[i]->equipmentIndex = i;
	}
}