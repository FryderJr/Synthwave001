// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPowerup.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASpeedPowerup::OnActivated(AActor* OtherActor)
{
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (!OtherCharacter)
	{
		return;
	}
	if (ActivatedFor)
	{
		return;
	}
	ActivatedFor = OtherCharacter;
	OtherCharacter->GetCharacterMovement()->MaxWalkSpeed = OtherCharacter->GetCharacterMovement()->GetMaxSpeed() * 2.0f;
	MeshComponent->SetVisibility(false);
}

void ASpeedPowerup::OnExpired()
{
	if (ActivatedFor)
	{
		ActivatedFor->GetCharacterMovement()->MaxWalkSpeed = ActivatedFor->GetCharacterMovement()->GetMaxSpeed() / 2.0f;
		ActivatedFor = nullptr;
		SetLifeSpan(1.0f);
	}
}

void ASpeedPowerup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ActivatedFor)
	{
		ActivatedFor->GetCharacterMovement()->MaxWalkSpeed = ActivatedFor->GetCharacterMovement()->GetMaxSpeed() / 2.0f;
		ActivatedFor = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}
