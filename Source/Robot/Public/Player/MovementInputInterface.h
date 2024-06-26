// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnhancedInputComponent.h"
#include "MovementInputInterface.generated.h"

class UCameraComponent;

UINTERFACE(MinimalAPI, Blueprintable)
class UMovementInputInterface : public UInterface
{
	GENERATED_BODY()
};

class IMovementInputInterface
{
	GENERATED_BODY()

public:
	// Pure virtual functions to be implemented by the inheriting class
	virtual void Move(const FInputActionValue& Value) = 0;
	virtual void Look(const FInputActionValue& Value) = 0;

	virtual UCameraComponent* GetCamera() const = 0;
};