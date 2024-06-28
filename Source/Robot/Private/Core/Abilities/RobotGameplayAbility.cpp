// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Abilities/RobotGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "Player/RobotPlayerController.h"

void URobotGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemComponent->MakeEffectContext();

	for (auto GameplayEffect : OngoingEffectsToApplyOnStart)
	{
		if (!GameplayEffect.Get()) continue;

		if (UAbilitySystemComponent* AbilityComponent = ActorInfo->AbilitySystemComponent.Get())
		{
			FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				if (!ActiveGEHandle.WasSuccessfullyApplied())
				{
					UE_LOG(LogTemp, Error, TEXT("Ability %s failed to apply startup effect to %s"), *GetName(), *GameplayEffect->GetName())
				}
			}
		}
	}

	if (IsInstantiated())
	{
		for (auto GameplayEffect : OngoingEffectsToRemoveOnEnd)
		{
			if (!GameplayEffect.Get()) continue;

			if (UAbilitySystemComponent* AbilityComponent = ActorInfo->AbilitySystemComponent.Get())
			{
				FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
				if (SpecHandle.IsValid())
				{
					FActiveGameplayEffectHandle ActiveGEHandle = AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
					if (!ActiveGEHandle.WasSuccessfullyApplied())
					{
						UE_LOG(LogTemp, Error, TEXT("Ability %s failed to apply runtime effect to %s"), *GetName(), *GameplayEffect->GetName())
					}
					else
					{
						RemoveOnEndEffectHandles.Add(ActiveGEHandle);
					}
				}
			}
		}
	}
}

void URobotGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UE_LOG(LogTemp, Warning, TEXT("EndAbility %s"), *GetName());
	if (IsInstantiated())
	{
		UE_LOG(LogTemp, Warning, TEXT("EndAbility %s IsInstantiated"), *GetName());
		for (FActiveGameplayEffectHandle ActiveEffectHandle : RemoveOnEndEffectHandles)
		{
			if (ActiveEffectHandle.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("EndAbility %s RemoveOnEndEffectHandles"), *GetName());
				ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle);
			}
		}

		RemoveOnEndEffectHandles.Empty();
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

TObjectPtr<ARobotPlayerController> URobotGameplayAbility::GetRobotPlayerController(const FGameplayAbilityActorInfo* ActorInfo) const
{
	return Cast<ARobotPlayerController>(ActorInfo->PlayerController.Get());
}

TObjectPtr<ACharacter> URobotGameplayAbility::GetCurrentCharacter(const FGameplayAbilityActorInfo* ActorInfo) const
{
	return ActorInfo->PlayerController.Get()->GetCharacter();
}
