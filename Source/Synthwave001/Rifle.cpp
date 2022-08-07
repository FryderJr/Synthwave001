// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text)

ARifle::ARifle()
{
	TrailTargetName = FName("BeamEnd");
	BaseDamage = 2.0f;
}

void ARifle::Fire()
{
	Super::Fire();

	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}

	FVector Direction = MyOwner->GetActorForwardVector();
	Direction.Y += FMath::RandRange(-0.1f, 0.1f);
	Direction.Z += FMath::RandRange(-0.02f, 0.02f);

	FVector TraceEnd = MeshComponent->GetSocketLocation(MuzzleSocketName) + Direction * 10000;
	
	//print(FString::Printf(TEXT("Trace end is (%f, %f, %f)"), TraceEnd.X, TraceEnd.Y, TraceEnd.Z));
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(MyOwner); //Igrone collision with owner
	CollisionQueryParams.AddIgnoredActor(this);	   //Ignore collision with gun itself
	CollisionQueryParams.bTraceComplex = true;	   //Trace with each individual triangle of complex mesh
	CollisionQueryParams.bReturnPhysicalMaterial = true;   //Return physical material
	//DrawDebugLine(GetWorld(), MeshComponent->GetSocketLocation(MuzzleSocketName), TraceEnd, FColor::Green, false, 0.5f, 2, 5.0f);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, MeshComponent->GetSocketLocation(MuzzleSocketName), TraceEnd, ECollisionChannel::ECC_Camera, CollisionQueryParams))
	{
		AActor* HitActor = HitResult.GetActor();

		//print(FString::Printf(TEXT("Actor hit is %s"), *HitActor->GetName()));

		TraceEnd = HitResult.ImpactPoint;

		UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, TraceEnd, HitResult, MyOwner->GetInstigatorController(), MyOwner, nullptr);
	}

	PlayEffects(TraceEnd);
}

void ARifle::PlayEffects(FVector TrailEnd)
{
	if (TrailEffect)
	{
		FVector SocketLocation = MeshComponent->GetSocketLocation(MuzzleSocketName);
		UParticleSystemComponent* Trail = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrailEffect, SocketLocation);
		if (Trail)
		{
			Trail->SetVectorParameter(TrailTargetName, TrailEnd);
		}
	}
}
