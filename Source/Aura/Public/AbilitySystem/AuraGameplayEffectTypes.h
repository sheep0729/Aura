#pragma once

#include "GameplayEffectTypes.h"
#include "AuraGameplayEffectTypes.generated.h"

class UAbilitySystemComponent;

USTRUCT()
struct FEffectActorInfo
{
	GENERATED_BODY()

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	AActor* AvatarActor;

	UPROPERTY()
	ACharacter* AvatarCharacter;

	UPROPERTY()
	AController* Controller;

	static FEffectActorInfo GetEffectActorInfo(UAbilitySystemComponent* AbilitySystemComponent);
};

USTRUCT()
struct FEffectContextData
{
	GENERATED_BODY()

	FGameplayEffectContextHandle EffectContext;

	UPROPERTY()
	FEffectActorInfo Source;

	UPROPERTY()
	FEffectActorInfo Target;

	static FEffectContextData GetEffectContextData(const FGameplayEffectModCallbackData& Data);
};