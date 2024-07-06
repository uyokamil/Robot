// © 2024, Team 2-M for the 2024 Climate Jam. All rights reserved.

#include "Core/Abilities/GA_MineResource.h"

UGA_MineResource::UGA_MineResource()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
}

bool UGA_MineResource::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGA_MineResource::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Play fire montage and wait for event telling us to spawn the projectile

	//UAT_WebSwing* Task = UAT_WebSwing::WebSwing(this, NAME_None, FGameplayTagContainer(), true);
	//Task->OnCompleted.AddDynamic(this, &UGA_WebSwing::OnCompleted);
	//Task->OnCancelled.AddDynamic(this, &UGA_WebSwing::OnCancelled);
	//Task->EventReceived.AddDynamic(this, &UGA_WebSwing::EventReceived);

	// Activate the task after we set it up.
	//Task->ReadyForActivation();
}

void UGA_MineResource::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UGA_MineResource::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_MineResource::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
}
