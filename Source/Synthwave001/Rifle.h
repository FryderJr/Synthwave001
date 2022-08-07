// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Rifle.generated.h"

/**
 * instantaneous type weapon that works on linetrace principle
 * assault rifles, machine guns
 */
UCLASS()
class SYNTHWAVE001_API ARifle : public AWeapon
{
	GENERATED_BODY()

	ARifle();
	
	virtual void Fire() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	UParticleSystem* TrailEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName TrailTargetName;

	void PlayEffects(FVector TrailEnd);
};
