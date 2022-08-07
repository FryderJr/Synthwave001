// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SynthwaveGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SYNTHWAVE001_API USynthwaveGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = Difficulty)
	int32 LongRangeEnemyPossibility = 15;

	UPROPERTY(BlueprintReadWrite, Category = Difficulty)
	int32 MeleeEnemyPossibility = 45;

	UPROPERTY(BlueprintReadWrite, Category = Difficulty)
	int32 BonusPossibility = 60;

	UFUNCTION(BlueprintCallable, Category = Difficulty)
	void SetLongRangeEnemyPossibility(int32 NewPossibility);

	UFUNCTION(BlueprintCallable, Category = Difficulty)
	void SetMeleeEnemyPossibility(int32 NewPossibility);

	UFUNCTION(BlueprintCallable, Category = Difficulty)
	void SetBonusPossibility(int32 NewPossibility);
};
