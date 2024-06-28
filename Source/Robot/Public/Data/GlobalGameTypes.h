// © 2024, Team 2-M for the 2024 Climate Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GlobalGameTypes.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	TArray<TSubclassOf<class UGameplayEffect>> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;
};