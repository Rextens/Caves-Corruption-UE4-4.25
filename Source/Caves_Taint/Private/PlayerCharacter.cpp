// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/Class.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//characterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character's mesh"));
	//characterMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> testMannequin(TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin"));
	const ConstructorHelpers::FObjectFinder<UAnimationAsset> walkAnimation(TEXT("/Game/AnimStarterPack/Walk_Fwd_Rifle_Ironsights"));

	if (testMannequin.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(testMannequin.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->AddWorldRotation(FRotator(0.0f, 270.0f, 0.0f));

		if (walkAnimation.Succeeded())
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			//GetMesh()->SetAnimation(walkAnimation.Object);
			//GetMesh()->Play(true);
			GetMesh()->PlayAnimation(walkAnimation.Object, true);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Loaded"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Could not load animation"));
		}

		characterView = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
		characterView->AttachTo(GetMesh(), FName("head"), EAttachLocation::KeepRelativeOffset, true);
		characterView->AddRelativeRotation(FRotator(180.0f, -90.0f, 90.0f));
		characterView->bUsePawnControlRotation = false;
		bUseControllerRotationPitch = true;
		//bUseControllerRotationYaw = true;
		//bUseControllerRotationRoll = true;
		characterView->bLockToHmd = true;
		
	}

	//GetMesh()
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	

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

	PlayerInputComponent->BindAxis("ChooseItem", this, &APlayerCharacter::turnMouseWheel);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	PlayerInputComponent->BindAction("Open/Close Gui", IE_Pressed, this, &APlayerCharacter::openEquipment);
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

void APlayerCharacter::turnMouseWheel(float value)
{
	if (value != 0.0f)
	{
		/*
		if (toolBar->choosenSlot + value < 0)
		{
			toolBar->choosenSlot = 8 + value + 1;
		}
		else if (toolBar->choosenSlot + value > 8)
		{
			toolBar->choosenSlot = -1 + value;
		}
		else
		{
			toolBar->choosenSlot += value;
		}
		toolBar->changeSlotInUse();
		*/
	}
}

void APlayerCharacter::openEquipment()
{
	/*
	if (!isGuiOpen)
	{
		equipmentWidget->AddToViewport();
		playerController->bShowMouseCursor = true;
	}
	else
	{
		equipmentWidget->RemoveFromParent();
		playerController->bShowMouseCursor = false;
	}

	isGuiOpen = !isGuiOpen;
	*/
}

void APlayerCharacter::hideHUD()
{
	/*
	if (showHUD)
	{
		toolBar->RemoveFromParent();
	}
	else
	{
		toolBar->AddToViewport();
	}
	showHUD = !showHUD;
	*/
}
