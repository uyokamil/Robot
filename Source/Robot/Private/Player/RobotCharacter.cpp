// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

#include "Player/RobotCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

#include "AbilitySystemComponent.h"
#include "Core/Abilities/RobotAttributeSet.h"

//////////////////////////////////////////////////////////////////////////
// ARobotCharacter

ARobotCharacter::ARobotCharacter()
{
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Gameplay Ability System
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void ARobotCharacter::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();

	if (IsValid(AbilitySystemComponent))
	{
		AttributeSet = AbilitySystemComponent->GetSet<URobotAttributeSet>();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No AbilitySystemComponent found in %s. Error!"), *GetName());
	}
}

void ARobotCharacter::Move(const FInputActionValue& Value)
{
	// Input
	FVector2D MovementVector = Value.Get<FVector2D>();

	// Move the character
	if (IsValid(Controller))
	{
		// Get forward vector from Control Rotation
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector from rotation
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Get right vector from rotation
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ARobotCharacter::Look(const FInputActionValue& Value)
{
}

UCameraComponent* ARobotCharacter::GetCamera() const
{
	return GetFollowCamera();
}