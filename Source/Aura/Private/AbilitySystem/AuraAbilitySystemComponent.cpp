// Copyright Yang Dong


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

void UAuraAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// IMPORTANT: OnGameplayEffectAppliedDelegateToSelf only called on server !!
	OnEffectAppliedDelegateHandle = OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::OnEffectApplied);

	AddSet<UAuraAttributeSet>();
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
