// © 2024, Team 2-M for the 2024 Climate Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/GlobalGameTypes.h"

#include "RobotCharacterDataAsset.generated.h"


UCLASS(BlueprintType, Blueprintable)
class ROBOT_API URobotCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FCharacterData CharacterData;
};