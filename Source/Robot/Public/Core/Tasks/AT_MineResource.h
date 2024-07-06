// © 2024, Team 2-M for the 2024 Climate Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_MineResource.generated.h"

/** Delegate type used, EventTag and Payload may be empty if it came from montage callbacks */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMineResourceDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTickTaskDelegate, float, DeltaTime);

UCLASS()
class ROBOT_API UAT_MineResource : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UAT_MineResource(const FObjectInitializer& ObjectInitializer);

	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;

	/** The montage completely finished playing */
	UPROPERTY(BlueprintAssignable)
	FMineResourceDelegate OnCompleted;

	/** The ability task was explicitly cancelled by another ability */
	UPROPERTY(BlueprintAssignable)
	FMineResourceDelegate OnCancelled;

	/** One of the triggering gameplay events happened */
	UPROPERTY(BlueprintAssignable)
	FMineResourceDelegate EventReceived;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAT_MineResource* MineResource(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		FGameplayTagContainer EventTags,
		bool bStopWhenAbilityEnds = true);

	//UFUNCTION(BlueprintCallable)
	// void SetSomeValue();

private:
	/** List of tags to match against gameplay events */
	UPROPERTY()
	FGameplayTagContainer EventTags;

	void OnAbilityCancelled();
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

	FDelegateHandle CancelledHandle;
	FDelegateHandle EventHandle;

	/** Avatar Actor Character */
	UPROPERTY()
	ACharacter* AvatarCharacter;
};
