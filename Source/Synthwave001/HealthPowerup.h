// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Powerup.h"
#include "HealthPowerup.generated.h"

/**
 * instantaneous powerup
 * adds 50 units of health to the character upon activation
 */
UCLASS()
class SYNTHWAVE001_API AHealthPowerup : public APowerup
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Powerups)
	float HealAmount = 50.0f;
	
	virtual void OnActivated(AActor* OtherActor) override;
};
