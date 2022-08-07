// Fill out your copyright notice in the Description page of Project Settings.


#include "Powerup.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text)

// Sets default values
APowerup::APowerup()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
	RootComponent = SceneComponent;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComponent"));
	MeshComponent->SetupAttachment(SceneComponent);

	MoveComponent = CreateDefaultSubobject<URotatingMovementComponent>(FName("MoveComponent"));
	MoveComponent->RotationRate = FRotator(0, 180, 0);

	PowerUpInterval = 0.0f;
	TotalNumberOfTicks = 0;

	bIsPowerupActive = false;
}

void APowerup::BeginPlay()
{
	Super::BeginPlay();

}

void APowerup::OnActivated(AActor* OtherActor)
{
	MeshComponent->SetVisibility(false);
	SetLifeSpan(1.0f);
}

void APowerup::OnExpired()
{
}

void APowerup::OnPowerupTicked()
{
}

void APowerup::ActivatePowerup(AActor* OtherActor)
{
	if (OtherActor == nullptr)
	{
		return;
	}
	OnActivated(OtherActor);

	bIsPowerupActive = true;

	if (PowerUpInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(PowerupTimerHandle, this, &APowerup::OnTickPowerup, PowerUpInterval, true);
	}
	else
	{
		OnTickPowerup();
	}
}

void APowerup::OnTickPowerup()
{
	TicksProccessed++;

	OnPowerupTicked();

	if (TicksProccessed >= TotalNumberOfTicks)
	{
		OnExpired();

		bIsPowerupActive = false;

		GetWorldTimerManager().ClearTimer(PowerupTimerHandle);
	}
}

