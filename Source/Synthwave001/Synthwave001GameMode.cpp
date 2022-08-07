// Copyright Epic Games, Inc. All Rights Reserved.

#include "Synthwave001GameMode.h"
#include "Synthwave001PlayerController.h"
#include "Synthwave001Character.h"
#include "GeneratedPlatform.h"
#include "LaunchPad.h"
#include "UObject/ConstructorHelpers.h"

ASynthwave001GameMode::ASynthwave001GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASynthwave001PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Synthwave001/Core/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASynthwave001GameMode::AddPlatform()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AGeneratedPlatform* Platform = GetWorld()->SpawnActor<AGeneratedPlatform>(PlatformClass, NextPlatformPoint, FRotator::ZeroRotator, SpawnParams);

	if (Platform)
	{
		if (CurrentPlatform)
		{
			CurrentPlatform->LaunchPad->Destination->SetWorldLocation(Platform->LevelStart->GetComponentLocation());
		}
		CurrentPlatform = Platform;
		NextPlatformPoint = CurrentPlatform->GetNextRandomPoint();
	}
}
