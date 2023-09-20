// Copyright Yang Dong


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "Algo/ForEach.h"
#include <Character/AuraCharacterBase.h>

void UAuraAbilitySystemComponent::GiveAbility(const TSubclassOf<UGameplayAbility> Ability, const int32 Level)
{
	FGameplayAbilitySpec AbilitySpec{Ability, Level};
    if (const UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
	{
		if (const FGameplayTag& InputTag = AuraGameplayAbility->GetStartupInputTag();InputTag.IsValid()) 
        {
			AbilitySpec.DynamicAbilityTags.AddTag(AuraGameplayAbility->GetStartupInputTag());
        }
	}

	GiveAbility(AbilitySpec);
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
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::OnEffectApplied);

	AddSet<UAuraAttributeSet>();
}


void UAuraAbilitySystemComponent::OnEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);

	if (ActiveEffectHandle.WasSuccessfullyApplied())
	{
		OnEffectAssetTags.Broadcast(AssetTags);
	}
}

bool UAuraAbilitySystemComponent::IsAbilitySpecMatchInputTag(const FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& InputTag)
{
	return AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag);
}
