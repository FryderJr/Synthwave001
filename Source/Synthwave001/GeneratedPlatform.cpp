// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratedPlatform.h"
#include "SynthwaveGameInstance.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "LaunchPad.h"
#include "Pickup.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text)

// Sets default values
AGeneratedPlatform::AGeneratedPlatform()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	RootComponent = SceneRoot;
	FloorLevel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Floor"));
	FloorLevel->SetupAttachment(SceneRoot);
	LevelStart = CreateDefaultSubobject<USceneComponent>(FName("LevelStart"));
	LaunchPadSpawn = CreateDefaultSubobject<USceneComponent>(FName("LaunchPadSpawn"));
	LevelStart->SetupAttachment(SceneRoot);
	LaunchPadSpawn->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AGeneratedPlatform::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	LaunchPad = GetWorld()->SpawnActor<ALaunchPad>(LaunchPadClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (LaunchPad)
	{
		LaunchPad->AttachToComponent(LaunchPadSpawn, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AGeneratedPlatform::PopulatePlatform()
{
	if (!SpawnLocationClass)
	{
		return;
	}
	if (SpawnTypeClasses.Num() == 0)
	{
		return;
	}
	TArray<UActorComponent*> SpawnPoints = GetComponentsByClass(SpawnLocationClass);

	if (SpawnPoints.Num() == 0)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto CurrentGameInstance = Cast<USynthwaveGameInstance>(GetGameInstance());

	if (!CurrentGameInstance)
	{
		return;
	}

	for (size_t i = 0; i < SpawnPoints.Num(); i++)
	{
		bool Spawned = false;
		int32 RandomSpawnClassIndex;
		int32 RandomValue;
		for (size_t j = 0; j < SpawnTypeClasses.Num(); j++)
		{
			if (Cast<ACharacter>(SpawnTypeClasses[j].GetDefaultObject()))
			{
				RandomValue = FMath::RandHelper(100);
				if (Cast<ABaseCharacter>(SpawnTypeClasses[j].GetDefaultObject()))
				{
					if (RandomValue <= CurrentGameInstance->LongRangeEnemyPossibility)
					{
						RandomSpawnClassIndex = j;
						Spawned = true;
						break;
					}
				}
				else
				{
					if (RandomValue <= CurrentGameInstance->MeleeEnemyPossibility)
					{
						RandomSpawnClassIndex = j;
						Spawned = true;
						break;
					}
				}
			} 
			else if (Cast<APickup>(SpawnTypeClasses[j].GetDefaultObject()))
			{
				RandomValue = FMath::RandHelper(100);
				if (RandomValue <= CurrentGameInstance->BonusPossibility)
				{
					RandomSpawnClassIndex = j;
					Spawned = true;
					break;
				}
			}
			else
			{
				RandomValue = FMath::RandHelper(100);
				if (RandomValue < 50)
				{
					RandomSpawnClassIndex = j;
					Spawned = true;
					break;
				}
			}
		}
		if (!Spawned)
		{
			continue;
		}
		USceneComponent* SceneSpawnPoint = Cast<USceneComponent>(SpawnPoints[i]);
		if (!SceneSpawnPoint)
		{
			continue;
		}
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnTypeClasses[RandomSpawnClassIndex], SceneSpawnPoint->GetComponentLocation(), FRotator::ZeroRotator, SpawnParams);
		if (SpawnedActor)
		{
			FVector SpawnedOrigin;
			FVector SpawnedExtent;
			FVector SpanwedLocation = SpawnedActor->GetActorLocation();
			SpawnedActor->GetActorBounds(true, SpawnedOrigin, SpawnedExtent);
			SpanwedLocation.Z += SpawnedExtent.Z;
			SpawnedActor->SetActorLocation(SpanwedLocation);
			if (!Cast<ACharacter>(SpawnedActor))
			{
				SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
		
	}
}

FVector AGeneratedPlatform::GetLevelStartPosition()
{
	return LevelStart->GetComponentLocation();
}

FVector AGeneratedPlatform::GetNextRandomPoint()
{
	FVector Center;
	FVector Extents;
	FloorLevel->Bounds.GetBox().GetCenterAndExtents(Center, Extents);

	float MaxX = Center.X + Extents.X * 2.0f;
	float MaxY = Center.Y + Extents.Y * 2.0f;

	FVector NewRandomLocation = FloorLevel->GetComponentLocation();
	NewRandomLocation.X = FMath::FRandRange(MaxX + 400.0f, MaxX + 1000.0f);
	//NewRandomLocation.Y = FMath::FRandRange(MaxY + 200.0f, MaxY + 400.0f);
	return NewRandomLocation;
}

