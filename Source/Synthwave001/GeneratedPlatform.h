// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneratedPlatform.generated.h"

class ALaunchPad;

UCLASS()
class SYNTHWAVE001_API AGeneratedPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratedPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Platform)
	void PopulatePlatform();

	UPROPERTY(EditDefaultsOnly, Category = Platform)
	TSubclassOf<ALaunchPad> LaunchPadClass;

	UPROPERTY(EditDefaultsOnly, Category = Platform)
	TSubclassOf<USceneComponent> SpawnLocationClass;

	UPROPERTY(EditDefaultsOnly, Category = Platform)
	TArray<TSubclassOf<AActor>> SpawnTypeClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Platform)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Platform)
	USceneComponent* LaunchPadSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UStaticMeshComponent* FloorLevel;

public:	

	ALaunchPad* LaunchPad;

	TArray<AActor*> GeneratedActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Platform)
	USceneComponent* LevelStart;

	FVector GetLevelStartPosition();

	FVector GetNextRandomPoint();
};
