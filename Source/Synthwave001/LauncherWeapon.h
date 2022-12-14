// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "LauncherWeapon.generated.h"

/**
 * launcher type shooting weapon
 * spawns projectiles (grenades, rockets, plasma bolts, etc)
 */
UCLASS()
class SYNTHWAVE001_API ALauncherWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AActor> ProjectileClass;

	virtual void Fire() override;
};
