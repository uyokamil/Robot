// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

#include "Player/RobotPlayerController.h"

// Input Includes
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player/MovementInputInterface.h"
#include "Camera/CameraComponent.h"

ARobotPlayerController::ARobotPlayerController()
{
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARobotPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetPawn())) return;

	IMovementInputInterface* MovementInputInterface = Cast<IMovementInputInterface>(GetPawn());
	if (MovementInputInterface)
	{
		// Set control rotation to match the camera
		UCameraComponent* CameraComponent = MovementInputInterface->GetCamera();
		if (CameraComponent)
		{
			SetControlRotation(CameraComponent->GetComponentRotation());
		}
	}
}

void ARobotPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARobotPlayerController::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARobotPlayerController::Look);
	}
}



void ARobotPlayerController::Move(const FInputActionValue& Value)
{
	if (IsValid(GetPawn()))
	{
		IMovementInputInterface* MovementInputInterface = Cast<IMovementInputInterface>(GetPawn());
		if (MovementInputInterface)
		{
			MovementInputInterface->Move(Value);
		}
	}
}

void ARobotPlayerController::Look(const FInputActionValue& Value)
{
	// implement for camera
}