// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class USphereComponent;
class UDecalComponent;
class APowerup;

UCLASS()
class SYNTHWAVE001_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	UDecalComponent* DecalComponent;

	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	TSubclassOf<APowerup> PowerupClass;

	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	float RespawnInterval;

	APowerup* PowerupInstance;

	FTimerHandle PickupRespawnHandler;

	UFUNCTION()
	void HandleSphereOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
