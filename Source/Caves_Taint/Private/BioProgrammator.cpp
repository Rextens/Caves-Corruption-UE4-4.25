// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "BioProgrammator.h"

ABioProgrammator::ABioProgrammator()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> widgetClassFinder(TEXT("/Game/Components/UI/ProgrammerInterface_BP"));
	MyWidgetClass = widgetClassFinder.Class;
}

void ABioProgrammator::activation()
{
	
	if (MyWidgetClass != nullptr)
	{
		programmatorWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), MyWidgetClass);
	
		if (programmatorWidget != nullptr)
		{
			programmatorWidget->AddToViewport();

			FInputModeUIOnly InputModeData;

			APlayerController* controllerReference = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			APlayerCharacter* characterReference = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			characterReference->isGuiOpen = true;
			characterReference->currentlyOpenUIs.Add(programmatorWidget);
			
			controllerReference->bShowMouseCursor = true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Couldn't load"));
	}
}
