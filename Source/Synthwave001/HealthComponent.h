// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangeSignature, UHealthComponent*, HealthComp, float, Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

/*
* Health component is used for handling damage/heal and friend or foe logic
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SYNTHWAVE001_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	// Crucial element of friend or foe system
	// friends have the same team
	// foes have different teams
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HealthComponent)
	uint8 Team;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = HealthComponent)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthComponent)
	float DefaultHealth = 100.0f;

	bool bIsDead;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:

	// blueprint assiagnable event
	// called when takes damage or heals
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnHealthChangeSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = HealthComponent)
	void Heal(float HealAmount);

	float GetHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = HealthComponent)
	static bool IsFriendly(AActor* ActorA, AActor* ActorB);
};
