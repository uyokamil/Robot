// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

#include "Player/RobotPlayerController.h"

// Input Includes
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player/MovementInputInterface.h"
#include "Camera/CameraComponent.h"

// Ability System
#include "Core/Components/RobotAbilitySystemComponent.h"
#include "Core/Abilities/RobotAttributeSet.h"
#include "Data/RobotCharacterDataAsset.h"

// Characters
#include "Player/RobotCharacter.h"

ARobotPlayerController::ARobotPlayerController()
{
	//bAbilitiesInitialized = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<URobotAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<URobotAttributeSet>(TEXT("AttributeSet"));
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

FCharacterData ARobotPlayerController::GetCharacterData() const
{
	return FCharacterData();
}

void ARobotPlayerController::SetCharacterData()
{
	CachedRobotCharacterData = RobotDataAsset->CharacterData;
}

bool ARobotPlayerController::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, FGameplayEffectContextHandle InEffectContext)
{
	return false;
}

void ARobotPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(RobotDataAsset))
	{
		SetCharacterData();
	}
}

void ARobotPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Check which character we're possessing
	if (TObjectPtr<ARobotCharacter> Robot = Cast<ARobotCharacter>(InPawn))
	{
		CurrentCharacterType = ECharacterType::Robot;
	}
	/*else if (TObjectPtr<ADroneCharacter> Drone = Cast<ADroneCharacter>(InPawn))
	{
		CurrentCharacterType = ECharacterType::Drone;
	}*/
}

void ARobotPlayerController::GiveAbilities(ECharacterType& CharacterType)
{
	for (auto DefaultAbility : CachedRobotCharacterData.Abilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DefaultAbility, 1, 0));
	}
}

void ARobotPlayerController::ApplyStartupEffects(ECharacterType& CharacterType)
{
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (auto CharacterEffect : CachedRobotCharacterData.Effects)
	{
		ApplyGameplayEffectToSelf(CharacterEffect, EffectContext);
	}
}

void ARobotPlayerController::InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication)
{
}

void ARobotPlayerController::Move(const FInputActionValue& Value)
{
	// Check if we should be frozen, or if we're stuck in recharging.
	if (AbilitySystemComponent->HasMatchingGameplayTag(FrozenTag) || AbilitySystemComponent->HasMatchingGameplayTag(RechargingTag))
	{
		return;
	}

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