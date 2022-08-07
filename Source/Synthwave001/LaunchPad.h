// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UBoxComponent;
/*
* launchpad actor placed on each platform enables movement from platform to platform both for player and enemy
*/
UCLASS()
class SYNTHWAVE001_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UStaticMeshComponent* Pad;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Launchpad)
	USoundWave* LaunchSound;

	UFUNCTION()
	void HandleBoxOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USceneComponent* Destination;
};
