#pragma once
#include "GameplayEffect.h"

struct FGameplayTagContainer;

class AuraAbilitySystemNativeLibrary
{
public:

	static TTuple<const FGameplayTagContainer*, const FGameplayTagContainer*> GetAllAggregatedTagsFromGameplayEffectSpec(const FGameplayEffectSpec& Spec);
	static bool IsEffectCauserLocallyControlled(const FGameplayEffectContextHandle& GameplayEffectContext);
};
