// Fill out your copyright notice in the Description page of Project Settings.


#include "SynthwaveGameInstance.h"

void USynthwaveGameInstance::SetLongRangeEnemyPossibility(int32 NewPossibility)
{
	LongRangeEnemyPossibility = NewPossibility;
}

void USynthwaveGameInstance::SetMeleeEnemyPossibility(int32 NewPossibility)
{
	MeleeEnemyPossibility = NewPossibility;
}

void USynthwaveGameInstance::SetBonusPossibility(int32 NewPossibility)
{
	BonusPossibility = NewPossibility;
}
