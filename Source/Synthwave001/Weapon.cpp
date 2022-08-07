// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("MeshComponent"));
	RootComponent = MeshComponent;
	MuzzleSocketName = FName("Muzzle");
}

void AWeapon::Fire()
{
	PlayMuzzle();
	LastTimeFired = GetWorld()->GetTimeSeconds();
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	TimeBetweenShots = 60.0f / FireRate;
	LastTimeFired = GetWorld()->GetTimeSeconds();
}

void AWeapon::PlayMuzzle()
{
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComponent, MuzzleSocketName);
	}
	if (ShootSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShootSound, MeshComponent->GetSocketLocation(MuzzleSocketName));
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::StartFire()
{
	float FireDelay = FMath::Max(LastTimeFired + TimeBetweenShots - GetWorld()->GetTimeSeconds(), 0.0f);
	GetWorldTimerManager().SetTimer(FTimeBetweenShots, this, &AWeapon::Fire, TimeBetweenShots, true, FireDelay);
}

void AWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(FTimeBetweenShots);
}

