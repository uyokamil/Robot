// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RobotPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class ROBOT_API ARobotPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARobotPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	//////////////////////////////
	/*	VARIABLES & PARAMETERS	*/
	//////////////////////////////

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	//////////////////////////////
	/*		FUNCTIONS			*/
	//////////////////////////////

	// TODO: Implement function for swapping characters
	/*
	* @brief Swaps the character the player is controlling.
	* This would need to swap control rotation and posessed pawn.
	* Something about switching out ability system abilities as well in here.
	*/

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
};
