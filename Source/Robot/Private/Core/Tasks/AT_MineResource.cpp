// © 2024, Team 2-M for the 2024 Climate Jam. All rights reserved.

#include "Core/Tasks/AT_MineResource.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilitySystemGlobals.h"


UAT_MineResource::UAT_MineResource(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAT_MineResource::Activate()
{
	AvatarCharacter = Cast<ACharacter>(AbilitySystemComponent->GetAvatarActor());
}

void UAT_MineResource::ExternalCancel()
{
}

FString UAT_MineResource::GetDebugString() const
{
	return FString();
}

void UAT_MineResource::OnDestroy(bool AbilityEnded)
{
	if (Ability)
	{
		Ability->OnGameplayAbilityCancelled.Remove(CancelledHandle);
		if (AbilityEnded)
		{
			// stop;
			UE_LOG(LogTemp, Warning, TEXT("Ability Ended"));
		}
	}

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

UAT_MineResource* UAT_MineResource::MineResource(UGameplayAbility* OwningAbility, FName TaskInstanceName, FGameplayTagContainer EventTags, bool bStopWhenAbilityEnds)
{
	UAT_MineResource* MyObj = NewAbilityTask<UAT_MineResource>(OwningAbility, TaskInstanceName);
	MyObj->EventTags = EventTags;

	return MyObj;
}

void UAT_MineResource::OnAbilityCancelled()
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
	}
}

void UAT_MineResource::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempData = *Payload;
		TempData.EventTag = EventTag;

		EventReceived.Broadcast(EventTag, TempData);
	}
}
