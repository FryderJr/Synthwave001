// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Synthwave001GameMode.generated.h"

class AGeneratedPlatform;

/*
* main level game mode handles platform generation
*/
UCLASS(minimalapi)
class ASynthwave001GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASynthwave001GameMode();

	UPROPERTY(EditDefaultsOnly, Category = PlatformGeneration)
	FVector NextPlatformPoint;

	UPROPERTY(EditDefaultsOnly, Category = PlatformGeneration)
	TSubclassOf<AGeneratedPlatform> PlatformClass;

	AGeneratedPlatform* CurrentPlatform;

	// generate next platform
	// called from the platform blueprint when player pawn enters overlap-zone around platform
	UFUNCTION(BlueprintCallable)
	void AddPlatform();
};



