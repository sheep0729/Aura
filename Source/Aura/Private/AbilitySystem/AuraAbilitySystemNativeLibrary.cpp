#include "AbilitySystem/AuraAbilitySystemNativeLibrary.h"

TTuple<const FGameplayTagContainer*, const FGameplayTagContainer*> AuraAbilitySystemNativeLibrary::GetAllAggregatedTagsFromGameplayEffectSpec(const FGameplayEffectSpec& Spec)
{
	const auto SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const auto TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();

	return MakeTuple(SourceTags, TargetTags);
}
