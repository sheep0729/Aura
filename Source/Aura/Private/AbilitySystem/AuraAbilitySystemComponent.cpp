// Copyright Yang Dong


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include <functional>


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "Algo/ForEach.h"

void UAuraAbilitySystemComponent::GiveAbility(const TSubclassOf<UGameplayAbility> Ability, const int32 Level)
{
	FGameplayAbilitySpec AbilitySpec{Ability, Level};
	if (const UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
	{
		AbilitySpec.DynamicAbilityTags.AddTag(AuraGameplayAbility->GetStartupInputTag());
		GiveAbility(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
}

void UAuraAbilitySystemComponent::OnAbilityInputHolding(const FGameplayTag& InputTag)
{
	FALSE_RETURN_VOID(InputTag.IsValid());

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (IsAbilitySpecMatchInputTag(AbilitySpec, InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
	FALSE_RETURN_VOID(InputTag.IsValid());

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (IsAbilitySpecMatchInputTag(AbilitySpec, InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

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

bool UAuraAbilitySystemComponent::IsAbilitySpecMatchInputTag(const FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& InputTag)
{
	return AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag);
}
