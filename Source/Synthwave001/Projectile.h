// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

/*
* projectile is spwaned by launcher weapon
*/
UCLASS()
class SYNTHWAVE001_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void SetDamage(float NewDamage);

	UPROPERTY(EditDefaultsOnly, Category = Components)
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = Components)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	UParticleSystem* ImpactEffect;

	UPROPERTY(BlueprintReadOnly, Category = Projectile)
	float Damage = 5.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
