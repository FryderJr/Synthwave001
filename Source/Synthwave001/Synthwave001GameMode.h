// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Synthwave001GameMode.generated.h"

class AGeneratedPlatform;

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

	UFUNCTION(BlueprintCallable)
	void AddPlatform();
};



