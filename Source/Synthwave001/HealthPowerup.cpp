// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPowerup.h"
#include "HealthComponent.h"

void AHealthPowerup::OnActivated(AActor* OtherActor)
{
	Super::OnActivated(OtherActor);
	UHealthComponent* HealthComp = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));
	if (HealthComp)
	{
		HealthComp->Heal(HealAmount);
	}
}
