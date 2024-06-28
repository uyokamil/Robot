// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/RobotData.h"

#include "RobotGameplayAbility.generated.h"

class ARobotPlayerController;

UCLASS()
class ROBOT_API URobotGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToApplyOnStart;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToRemoveOnEnd;

	TArray<FActiveGameplayEffectHandle> RemoveOnEndEffectHandles;

	// Normally, I'd like to have a return function for the specific character type. But since we have two, I'm going to omit.
	// But I'll drop this here for now because that's where our ASC is.
	TObjectPtr<ARobotPlayerController> GetRobotPlayerController(const FGameplayAbilityActorInfo* ActorInfo) const;

	TObjectPtr<ACharacter> GetCurrentCharacter(const FGameplayAbilityActorInfo* ActorInfo) const;
};
