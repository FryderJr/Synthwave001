// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SynthwaveGameInstance.generated.h"

/**
 * game instace stores probabilities of spawn for various types of actors, that can be placed on platform (enemies, bonuses, obstacles)
 */
UCLASS()
class SYNTHWAVE001_API USynthwaveGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	// shooting enemy placement probability
	UPROPERTY(BlueprintReadWrite, Category = Difficulty)
	int32 LongRangeEnemyPossibility = 15;

	// melee enemy placement probability
	UPROPERTY(BlueprintReadWrite, Category = Difficulty)
	int32 MeleeEnemyPossibility = 45;

	// bonuses placement probability
	UPROPERTY(BlueprintReadWrite, Category = Difficulty)
	int32 BonusPossibility = 60;

	UFUNCTION(BlueprintCallable, Category = Difficulty)
	void SetLongRangeEnemyPossibility(int32 NewPossibility);

	UFUNCTION(BlueprintCallable, Category = Difficulty)
	void SetMeleeEnemyPossibility(int32 NewPossibility);

	UFUNCTION(BlueprintCallable, Category = Difficulty)
	void SetBonusPossibility(int32 NewPossibility);
};
