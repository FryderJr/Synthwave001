// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Powerup.h"
#include "SpeedPowerup.generated.h"

/**
 * continuos powerup
 * multiplies character speed by the factor of 2 on activation
 * divides character speed by the factor of 2 on expire (removes powerup effect)
 */
UCLASS()
class SYNTHWAVE001_API ASpeedPowerup : public APowerup
{
	GENERATED_BODY()

protected:

	ACharacter* ActivatedFor = nullptr;

	virtual void OnActivated(AActor* OtherActor) override;

	virtual void OnExpired() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
