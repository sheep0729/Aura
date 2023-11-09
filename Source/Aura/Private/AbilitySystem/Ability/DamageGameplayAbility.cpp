// Copyright Yang Dong


#include "AbilitySystem/Ability/DamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	const FGameplayEffectSpecHandle DamageEffect = MakeOutgoingGameplayEffectSpec(DamageEffectClass, GetAbilityLevel());
	for (const auto& Pair : DamageMap)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const float Damage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffect, DamageType, Damage);
	}
	
	const auto Source = GetAbilitySystemComponentFromActorInfo_Checked();
	const auto Target = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Source->ApplyGameplayEffectSpecToTarget(*DamageEffect.Data, Target);
}
