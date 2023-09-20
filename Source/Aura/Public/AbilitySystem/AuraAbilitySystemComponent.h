// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Marco.h"
#include "AuraAbilitySystemComponent.generated.h"


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

	UFUNCTION(Client, Reliable)
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
	REF_GETTER(OnEffectAssetTags);

	REF_GETTER(OnDamaged);
	CONST_REF_GETTER(OnDamaged);

protected:
	virtual void InitializeComponent() override;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectAssetTagsSingature, FGameplayTagContainer /* MessageTags */);
	FOnEffectAssetTagsSingature OnEffectAssetTags;

private:
	bool IsAbilitySpecMatchInputTag(const FGameplayAbilitySpec& AbilitySpec,const FGameplayTag& InputTag);
	
	FDelegateHandle OnEffectAppliedDelegateHandle;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDamagedSingature, float, /*Damage, */float, /*OldHealth, */float/* , NewHealth*/);
	FOnDamagedSingature OnDamaged;
};
