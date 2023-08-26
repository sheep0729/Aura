// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.h"
#include "Marco.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectAssetTagsSingature, const FGameplayTagContainer& /* AssetTags */);

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	const UAuraAttributeSet* GetAuraAttributeSet(TSubclassOf<UAttributeSet> AttributeSetClass) const;

	REF_GETTER(OnEffectAssetTags);
protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	FOnEffectAssetTagsSingature OnEffectAssetTags;
private:
	FDelegateHandle OnEffectAppliedDelegateHandle;
};
