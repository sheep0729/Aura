// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Marco.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectAssetTagsSingature, FGameplayTagContainer /* MessageTags */);

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	using UAbilitySystemComponent::GiveAbility;
	void GiveAbility(TSubclassOf<UGameplayAbility> Ability, int32 Level);
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputHolding(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);
	virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec& GameplayEffect, FPredictionKey PredictionKey) override;
	
	REF_GETTER(OnEffectAssetTags);

protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;

	UFUNCTION(Client, Reliable)
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	FOnEffectAssetTagsSingature OnEffectAssetTags;

private:
	bool IsAbilitySpecMatchInputTag(const FGameplayAbilitySpec& AbilitySpec,const FGameplayTag& InputTag);
	
	FDelegateHandle OnEffectAppliedDelegateHandle;
};
