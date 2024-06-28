// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Abilities/GameplayAbility.h"
#include "AbilitySystemInterface.h"
#include "Data/GlobalGameTypes.h"

#include "RobotPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class URobotAbilitySystemComponent;
class URobotAttributeSet;
class UGameplayEffect;
class URobotGameplayAbility;

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Robot	UMETA(DisplayName = "Robot Character"),
	Drone	UMETA(DisplayName = "Drone Character")
};

UCLASS()
class ROBOT_API ARobotPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//////////////////////////////
	/*		FUNCTIONS			*/
	//////////////////////////////
	ARobotPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// HELPER FUNCTIONS
	UFUNCTION(BlueprintCallable)
	FCharacterData GetCharacterData() const;

	void SetCharacterData();

	// ABILITY FUNCTIONS
	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, FGameplayEffectContextHandle InEffectContext);

protected:
	//////////////////////////////
	/*	VARIABLES & PARAMETERS	*/
	//////////////////////////////

	/** Ability System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URobotAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(Transient)
	TObjectPtr<URobotAttributeSet> AttributeSet;

	UPROPERTY()
	FCharacterData CachedRobotCharacterData;

	UPROPERTY(EditDefaultsOnly)
	class URobotCharacterDataAsset* RobotDataAsset;

	// ==================== //
	// GAMEPLAY TAGS
	// ==================== //

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag FrozenTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag RechargingTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer RobotTags;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer DroneTags;

	virtual URobotAbilitySystemComponent* GetAbilitySystemComponent() { return AbilitySystemComponent; }

	//////////////////////////////
	/*		FUNCTIONS			*/
	//////////////////////////////

	virtual void PostInitializeComponents() override;

	void OnPossess(APawn* InPawn) override;

	// ABILITY FUNCTIONS
	void GiveAbilities(ECharacterType& CharacterType);
	void ApplyStartupEffects(ECharacterType& CharacterType);
	virtual void InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication = false);

private:
	//////////////////////////////
	/*	VARIABLES & PARAMETERS	*/
	//////////////////////////////

	// Character
	ECharacterType CurrentCharacterType;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

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
