// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"

#include "RobotCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UAbilitySystemComponent;
class URobotAttributeSet;

UCLASS(config=Game)
class ARobotCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	//////////////////////////////
	/*		FUNCTIONS			*/
	//////////////////////////////

	ARobotCharacter();

	// To add mapping context
	virtual void BeginPlay();

	// Getters / Setters

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayAbilitySystem", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayAbilitySystem", meta = (AllowPrivateAccess = "true"))
	const URobotAttributeSet* AttributeSet;

private:
	//////////////////////////////
	/*	VARIABLES & PARAMETERS	*/
	//////////////////////////////

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
};