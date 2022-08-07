// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherWeapon.h"
#include "Projectile.h"

void ALauncherWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}

	if (!ProjectileClass)
	{
		return;
	}

	Super::Fire();

	FRotator Rotation = MyOwner->GetActorForwardVector().Rotation();
	FVector SocketLocation = MeshComponent->GetSocketLocation(MuzzleSocketName);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto Projectile = Cast<AProjectile>(GetWorld()->SpawnActor<AActor>(ProjectileClass, SocketLocation, Rotation, SpawnParams));
	if (Projectile)
	{
		APawn* MyIntigator = Cast<APawn>(GetOwner());
		if (MyIntigator)
		{
			Projectile->SetInstigator(MyIntigator);
			Projectile->SetDamage(BaseDamage);
		}
	}
}
