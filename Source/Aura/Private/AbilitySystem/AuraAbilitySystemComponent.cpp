// Copyright Yang Dong


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/AuraAttributeSet.h"

const UAuraAttributeSet* UAuraAbilitySystemComponent::GetAuraAttributeSet(TSubclassOf<UAttributeSet> AttributeSetClass) const
{
	return CastChecked<UAuraAttributeSet>(GetAttributeSet(AttributeSetClass));
}
