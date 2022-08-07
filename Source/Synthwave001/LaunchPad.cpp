// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "JumpFromPlatfrom.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	RootComponent = BoxComponent;
	Pad = CreateDefaultSubobject<UStaticMeshComponent>(FName("Pad"));
	Pad->SetupAttachment(BoxComponent);
	Destination = CreateDefaultSubobject<USceneComponent>(FName("Destination"));
	Destination->SetupAttachment(BoxComponent);
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ALaunchPad::HandleBoxOverlap);
}

void ALaunchPad::HandleBoxOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor)
	{
		return;
	}
	if (!OtherActor->GetClass()->ImplementsInterface(UJumpFromPlatfrom::StaticClass()))
	{
		return;
	}
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
	IJumpFromPlatfrom::Execute_JumpTo(OtherActor, Destination->GetComponentLocation(), 4.0f);
}