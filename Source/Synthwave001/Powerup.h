// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Powerup.generated.h"

class URotatingMovementComponent;

UCLASS()
class SYNTHWAVE001_API APowerup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerup();

	virtual void BeginPlay() override;

	virtual void OnActivated(AActor* OtherActor);

	virtual void OnExpired();

	virtual void OnPowerupTicked();

	void ActivatePowerup(AActor* OtherActor);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	URotatingMovementComponent* MoveComponent;

	/* Time between powerup ticks */
	UPROPERTY(EditDefaultsOnly, Category = Powerups)
	float PowerUpInterval;

	/* Total time we apply powerup effect */
	UPROPERTY(EditDefaultsOnly, Category = Powerups)
	int32 TotalNumberOfTicks;

	/* Keeps state of the powerup */
	bool bIsPowerupActive;

	FTimerHandle PowerupTimerHandle;

	int32 TicksProccessed;

	virtual void OnPowerupStateChanged(bool bNewState) PURE_VIRTUAL(APowerup::OnPowerupStateChanged, );

	UFUNCTION()
	void OnTickPowerup();
};
