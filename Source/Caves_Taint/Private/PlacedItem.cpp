// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacedItem.h"

// Sets default values
APlacedItem::APlacedItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object's mesh"));
	mesh->AttachTo(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshFinder(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	mesh->SetStaticMesh(meshFinder.Object);
	mesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void APlacedItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlacedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

