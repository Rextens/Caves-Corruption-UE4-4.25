// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "UObject/Class.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "VoxelWorldGenerators/VoxelWorldGeneratorHelpers.h"
#include "PlacedRock.h"
#include "NONEReference.h"
#include "SaveWorld.h"
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
	addItemToEquipment("NotStackable", nullptr, false, false, 10);

	playerController = Cast<ACharacterController>(GetController());
	
	if (playerController)
	{
		playerController->bEnableClickEvents = true;
		playerController->bEnableMouseOverEvents = true;
	}	

	USaveWorld* saveWorldInstance = Cast<USaveWorld>(UGameplayStatics::CreateSaveGameObject(USaveWorld::StaticClass()));

	if (saveWorldInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("loaded"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not loaded"));
	}

//	for (int i = 0; i < 9; ++i)
//	{
//		itemsInToolBar.Add(nullptr);
//	}

	FVector test0 = FVector(15.0f, 15.0f, 15.0f);
	FVector test1 = FVector(15.0f, 15.0f, 15.0f);
		test0 = test0 + 2000.0f;

		bool test2 = false;

		if (test0 == test1 + 2000.0f)
		{
			test2 = true;
		}
	
		int32 test3;

		if (test2)
		{
			test3 = 1;
		}
		else
		{
			test3 = 0;
		}

//	if (GEngine)
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("X: %f, Y: %f, Z: %f"), test0.X, test0.Y, test0.Z));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("test: %i"), test3));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	checkChunks();
	removeChunks();
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
	if (!isGuiOpen)
	{
		FHitResult hitResult;
		GetWorld()->LineTraceSingleByChannel(hitResult, characterView->GetComponentLocation(), characterView->GetForwardVector() * 1000.0f + characterView->GetComponentLocation(), ECC_Visibility);
		DrawDebugLine(GetWorld(), characterView->GetComponentLocation(), characterView->GetForwardVector() * 1000.0f + characterView->GetComponentLocation(), FColor::Red, false, 2.0f);

		AActiveableItem* activeable = Cast<AActiveableItem>(hitResult.Actor);

		if (!activeable)
		{
			if (selectedItem < itemsInEquipment.Num())
			{
				if (itemsInEquipment[selectedItem]->placedItemClass != nullptr && itemsInEquipment[selectedItem] != nullptr)
				{
					FRotator Rotation(0.0f, 0.0f, 0.0f);
					FActorSpawnParameters SpawnInfo;

					GetWorld()->SpawnActor<APlacedItem>(itemsInEquipment[selectedItem]->placedItemClass, hitResult.Location, Rotation, SpawnInfo);
					removeItemFromEquipment(itemsInEquipment[selectedItem]->equipmentIndex);
				}
			}
		}
		else
		{
			activeable->activation();
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

void APlayerCharacter::addItemReferenceToEquipment(UItem* itemReference)
{
	if (itemReference != nullptr)
	{
		if (itemReference->stackable)
		{
			UStackableItem* stackableItem = NewObject<UStackableItem>();

			stackableItem->itemName = itemReference->itemName;
			stackableItem->placedItemClass = itemReference->placedItemClass;

			stackableItem->stack = Cast<UStackableItem>(itemReference)->stack;
			itemsInEquipment.Add(stackableItem);
			itemsInEquipment[itemsInEquipment.Num() - 1]->equipmentIndex = itemsInEquipment.Num() - 1;
		}
		else
		{
			UItem* createdItem = NewObject<UItem>();

			createdItem->itemName = itemReference->itemName;
			createdItem->placedItemClass = itemReference->placedItemClass;

			itemsInEquipment.Add(createdItem);
			itemsInEquipment[itemsInEquipment.Num() - 1]->equipmentIndex = itemsInEquipment.Num() - 1;
		}
	}
}

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

void APlayerCharacter::insertItemReferenceToEquipment(UItem* itemReference, int32 index)
{
	if (itemReference->stackable)
	{
		UStackableItem* stackableItemReference = Cast<UStackableItem>(DuplicateObject<UItem>(itemReference, this));

		itemsInEquipment.SetNum(itemsInEquipment.Num() + 1);

		for (int i = itemsInEquipment.Num() - 1; i >= index + 1; --i)
		{
			itemsInEquipment[i] = itemsInEquipment[i - 1];
		}

		itemsInEquipment[index] = stackableItemReference;
	}
	else
	{
		UItem* duplicatedItemReference = DuplicateObject<UItem>(itemReference, this);

		itemsInEquipment.SetNum(itemsInEquipment.Num() + 1);

		for (int i = itemsInEquipment.Num() - 1; i >= index + 1; --i)
		{
			itemsInEquipment[i] = itemsInEquipment[i - 1];
		}

		itemsInEquipment[index] = duplicatedItemReference;
	}

	updateItemIndexes();
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

void APlayerCharacter::saveCube(FVector cubeLocation)
{

}


FVector APlayerCharacter::getPlayerCube()
{
	return FVector(floor(GetActorLocation().X / 4096.0f), floor(GetActorLocation().Y / 4096.0f), floor(GetActorLocation().Z / 4096.0f));
}

void APlayerCharacter::spawnStartingChunkCubes()
{
	FVector playerCube = getPlayerCube();
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				mainBoxes[i][j][k] = GetWorld()->SpawnActor<AchunkBox>();	
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %f, y: %f, z: %f"), playerCube.X, playerCube.Y, playerCube.Z));
				mainBoxes[i][j][k]->SetActorLocation(FVector((playerCube.X + i - 1) * 8192.0f,
					(playerCube.Y + j - 1) * 8192.0f,
					(playerCube.Z + k - 1) * 8192.0f));
			}
		}
	}
}

void APlayerCharacter::checkChunks()
{
	FVector playerChunk = getPlayerCube();
	for (int x = -renderRadius; x < renderRadius; ++x)
	{
		for (int y = -renderRadius; y < renderRadius; ++y)
		{
			for (int z = -renderRadius; z < renderRadius; ++z)
			{
				FVector currentChunk = getPlayerCube();
				FVector finalLocation = FVector(4096.0f * (currentChunk.X + x) + 2048.0f, 4096.0f * (currentChunk.Y + y) + 2048.0f, 4096.0f * (currentChunk.Z + z) + 2048.0f);
				
				if (findChunk(finalLocation) == -1)
				{
					chunks.Add(GetWorld()->SpawnActor<AchunkBox>());
					chunks[chunks.Num() - 1]->SetActorLocation(finalLocation);
				}
			}
		}
	}
}

void APlayerCharacter::removeChunks()
{
	for (int i = 0; i < chunks.Num(); ++i)
	{
		if (abs(floor(chunks[i]->GetActorLocation().X / 4096.0f) - getPlayerCube().X) > renderRadius ||
			abs(floor(chunks[i]->GetActorLocation().Y / 4096.0f) - getPlayerCube().Y) > renderRadius ||
			abs(floor(chunks[i]->GetActorLocation().Z / 4096.0f) - getPlayerCube().Z) > renderRadius)
		{
			chunks[i]->Destroy();
			chunks.RemoveAt(i);
		}
	}
}

int32 APlayerCharacter::findChunk(FVector position)
{
	for (int i = 0; i < chunks.Num(); ++i)
	{
		if (chunks[i]->GetActorLocation() == position)
		{
			return i;
		}
	}
	return -1;
}