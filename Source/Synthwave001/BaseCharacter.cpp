// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "AIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HealthComponent.h"
#include "Weapon.h"

ABaseCharacter::ABaseCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->AirControl = 0.0f;

	WeaponSocketName = FName("WeaponSocket");

	// Create health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComp"));
	HealthComponent->bEditableWhenInherited = true;
	//HealthComponent->RegisterComponent();

	MaterialPulseParameterName = FName("LastTimeDamageTaken");

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// binding health component OnHealthChanged with character OnHealthChanged
	HealthComponent->OnHealthChanged.AddDynamic(this, &ABaseCharacter::OnHealthChanged);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//Spawn Weapon
	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
	}
}

void ABaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// make sure there character weapon is also destroyed
	CurrentWeapon->SetLifeSpan(1.0f);
	Super::EndPlay(EndPlayReason);
}

void ABaseCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void ABaseCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

void ABaseCharacter::JumpTo_Implementation(FVector Destination, float Duration)
{
	if (Duration <= 0)
	{
		return;
	}
	FVector TempLocation = FVector();
	TempLocation.X = (Destination.X - GetActorLocation().X) / Duration;
	TempLocation.Y = (Destination.Y - GetActorLocation().Y) / Duration;
	TempLocation.Z = (Destination.Z - (GetActorLocation().Z - (((FMath::Pow(Duration, 2)) * 0.5f) * 980.0f))) / Duration;
	GetMovementComponent()->StopActiveMovement();
	LaunchCharacter(TempLocation, true, true);
}

void ABaseCharacter::OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	// implementing character material pulse when he takes damage
	if (MatInst == nullptr)
	{
		MatInst = GetMesh()->CreateAndSetMaterialInstanceDynamicFromMaterial(0, GetMesh()->GetMaterial(0));
	}
	if (MatInst)
	{
		MatInst->SetScalarParameterValue(MaterialPulseParameterName, GetWorld()->GetTimeSeconds());
	}

	// character death logic impleementation
	if (Health <= 0.0f && !bDied)
	{
		bDied = true;

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DetachFromControllerPendingDestroy();
		SetLifeSpan(10.0f);
		if (CurrentWeapon)
		{
			CurrentWeapon->StopFire();
			CurrentWeapon->SetLifeSpan(10.0f);
		}
	}
}

/*
* deactivate path following component due to interference in jumping mechanic
*/
void ABaseCharacter::Falling()
{
	Super::Falling();
	auto CurrentController = Cast<AAIController>(GetController());
	if (CurrentController)
	{
		CurrentController->GetPathFollowingComponent()->Deactivate();
	}
}

/*
* activate path following component when character lands
*/
void ABaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	auto CurrentController = Cast<AAIController>(GetController());
	if (CurrentController)
	{
		CurrentController->GetPathFollowingComponent()->Activate();
	}
}
