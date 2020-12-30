// Fill out your copyright notice in the Description page of Project Settings.


#include "chunkBox.h"
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

