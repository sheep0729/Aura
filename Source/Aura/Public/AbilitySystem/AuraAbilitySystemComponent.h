// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.h"
#include "GameplayTagContainer.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectAssetTagsSingature, FGameplayTagContainer /* MessageTags */);

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	REF_GETTER(OnEffectAssetTags);

protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	FOnEffectAssetTagsSingature OnEffectAssetTags;

private:
	FDelegateHandle OnEffectAppliedDelegateHandle;
};
