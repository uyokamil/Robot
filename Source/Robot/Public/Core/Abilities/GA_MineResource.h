// © 2024, Team 2-M for the 2024 Climate Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Abilities/RobotGameplayAbility.h"
#include "GA_MineResource.generated.h"

UCLASS()
class ROBOT_API UGA_MineResource : public URobotGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_MineResource();

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	float Range;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly Category = "Resource")
	//float MiningTime;

	UFUNCTION()
	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void EventReceived(FGameplayTag EventTag, FGameplayEventData EventData);
};
