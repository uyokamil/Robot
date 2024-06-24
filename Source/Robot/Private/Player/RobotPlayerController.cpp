// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

#include "Player/RobotPlayerController.h"

// Input Includes
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ARobotPlayerController::ARobotPlayerController()
{
}

//////////////////////////////////////////////////////////////////////////
// Input

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
}

void ARobotPlayerController::Look(const FInputActionValue& Value)
{
}
