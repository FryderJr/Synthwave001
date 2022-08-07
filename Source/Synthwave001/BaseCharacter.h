// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JumpFromPlatfrom.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UHealthComponent;
/**
 * parent class for all shooting characters in the game both player and enemy
 */
UCLASS()
class SYNTHWAVE001_API ABaseCharacter : public ACharacter, public IJumpFromPlatfrom
{
	GENERATED_BODY()
	
public:
	ABaseCharacter();

	// Called when game starts or when spawned
	virtual void BeginPlay() override;

	// Called before character destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Start volley fire
	UFUNCTION(BlueprintCallable)
	void StartFire();

	// Stop volley fire
	UFUNCTION(BlueprintCallable)
	void StopFire();

	// Jumping from platform
	virtual void JumpTo_Implementation(FVector Destination, float Duration) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Character)
	FName WeaponSocketName;

	// Pulse parameter in material
	UPROPERTY(EditDefaultsOnly, Category = Damage)
	FName MaterialPulseParameterName;

	AWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = Character)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(BlueprintReadOnly, Category = Character)
	bool bDied;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UHealthComponent* HealthComponent;

	// Dynamic matrial to pulse
	UMaterialInstanceDynamic* MatInst;

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	virtual void Falling() override;

	virtual void Landed(const FHitResult& Hit) override;
};
