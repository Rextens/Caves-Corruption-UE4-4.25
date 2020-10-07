// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Item.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CAVES_TAINT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

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
};
