#include "AbilitySystem/AuraAbilitySystemNativeLibrary.h"

#include "Marco.h"
#include "GameFramework/Character.h"

TTuple<const FGameplayTagContainer*, const FGameplayTagContainer*> AuraAbilitySystemNativeLibrary::GetAllAggregatedTagsFromGameplayEffectSpec(
	const FGameplayEffectSpec& Spec)
{
	const auto SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const auto TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();

	return MakeTuple(SourceTags, TargetTags);
}

bool AuraAbilitySystemNativeLibrary::IsEffectCauserLocallyControlled(const FGameplayEffectContextHandle& GameplayEffectContext)
{
	const auto SourceCharacter = Cast<ACharacter>(GameplayEffectContext.GetEffectCauser());
	INVALID_RETURN_OBJECT(SourceCharacter, false);

	return SourceCharacter->IsLocallyControlled();
}
