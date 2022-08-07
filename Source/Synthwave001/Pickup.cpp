// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Powerup.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text)

// Sets default values
APickup::APickup()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("SphereComp"));
	SphereComponent->SetSphereRadius(75.0f);
	RootComponent = SphereComponent;

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(FName("DecalComp"));
	DecalComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	DecalComponent->DecalSize = FVector(64, 75, 75);
	DecalComponent->SetupAttachment(RootComponent);

	RespawnInterval = 5.0f;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	if (PowerupClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Powerup class is not defined in %s!"), *GetName());
		return;
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PowerupInstance = GetWorld()->SpawnActor<APowerup>(PowerupClass, GetTransform(), SpawnParams);
	PowerupInstance->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	OnActorBeginOverlap.AddDynamic(this, &APickup::HandleSphereOverlap);
}

void APickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PowerupInstance)
	{
		PowerupInstance->SetLifeSpan(1.0f);
	}
	Super::EndPlay(EndPlayReason);
}


void APickup::HandleSphereOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	auto OtherCharacter = Cast<ACharacter>(OtherActor);
	if (!OtherCharacter)
	{
		return;
	}
	if (!PowerupInstance)
	{
		return;
	}
	PowerupInstance->ActivatePowerup(OtherActor);
	PowerupInstance = nullptr;
}

