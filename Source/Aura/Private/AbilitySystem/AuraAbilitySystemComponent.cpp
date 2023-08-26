// Copyright Yang Dong


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/AuraAttributeSet.h"

const UAuraAttributeSet* UAuraAbilitySystemComponent::GetAuraAttributeSet(TSubclassOf<UAttributeSet> AttributeSetClass) const
{
	return CastChecked<UAuraAttributeSet>(GetAttributeSet(AttributeSetClass));
}

void UAuraAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OnEffectAppliedDelegateHandle = OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::OnEffectApplied);
}

void UAuraAbilitySystemComponent::UninitializeComponent()
{
	Super::UninitializeComponent();

	OnGameplayEffectAppliedDelegateToSelf.Remove(OnEffectAppliedDelegateHandle);
}


void UAuraAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);

	OnEffectAssetTags.Broadcast(AssetTags);
}
