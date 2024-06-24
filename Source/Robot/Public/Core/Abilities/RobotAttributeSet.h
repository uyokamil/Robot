// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RobotAttributeSet.generated.h"

// Attributes.h Macros
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ROBOT_API URobotAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	URobotAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "GameplayAttribute")
	FGameplayAttributeData Battery;
	ATTRIBUTE_ACCESSORS(URobotAttributeSet, Battery)

	UPROPERTY(BlueprintReadOnly, Category = "GameplayAttribute")
	FGameplayAttributeData MaxBattery;
	ATTRIBUTE_ACCESSORS(URobotAttributeSet, MaxBattery)
};