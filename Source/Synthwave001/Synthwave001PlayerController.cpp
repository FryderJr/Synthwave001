// Copyright Epic Games, Inc. All Rights Reserved.

#include "Synthwave001PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Synthwave001Character.h"
#include "Engine/World.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text)

ASynthwave001PlayerController::ASynthwave001PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASynthwave001PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	MoveToMouseCursor();
}

void ASynthwave001PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Click", IE_Pressed, this, &ASynthwave001PlayerController::OnFirePressed);
	InputComponent->BindAction("Click", IE_Released, this, &ASynthwave001PlayerController::OnFireReleased);

	InputComponent->BindAxis(FName("MoveForward"), this, &ASynthwave001PlayerController::MoveForward);
	InputComponent->BindAxis(FName("MoveRight"), this, &ASynthwave001PlayerController::MoveRight);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASynthwave001PlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASynthwave001PlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ASynthwave001PlayerController::OnResetVR);
}

void ASynthwave001PlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASynthwave001PlayerController::MoveForward(float Value)
{
	APawn* const MyPawn = GetPawn();

	if (MyPawn)
	{
		MyPawn->AddMovementInput(MyPawn->GetActorForwardVector() * Value);
	}

}

void ASynthwave001PlayerController::MoveRight(float Value)
{
	APawn* const MyPawn = GetPawn();

	if (MyPawn)
	{
		MyPawn->AddMovementInput(MyPawn->GetActorRightVector() * Value);
	}
}

void ASynthwave001PlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ASynthwave001PlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ASynthwave001PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		FRotator PawnRotation = MyPawn->GetActorRotation();

		MyPawn->SetActorRotation(UKismetMathLibrary::RInterpTo(PawnRotation, FRotator(PawnRotation.Pitch, UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), DestLocation).Yaw, PawnRotation.Roll) , GetWorld()->DeltaTimeSeconds, 5));
	}
}

void ASynthwave001PlayerController::OnFirePressed()
{
	ASynthwave001Character* MyCharacter = Cast<ASynthwave001Character>(GetPawn());
	if (MyCharacter)
	{
		MyCharacter->StartFire();
	}
}

void ASynthwave001PlayerController::OnFireReleased()
{
	ASynthwave001Character* MyCharacter = Cast<ASynthwave001Character>(GetPawn());
	if (MyCharacter)
	{
		MyCharacter->StopFire();
	}
}
