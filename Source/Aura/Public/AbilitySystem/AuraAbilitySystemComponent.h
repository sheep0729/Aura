// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.h"
#include "AuraAbilitySystemComponent.generated.h"

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	const UAuraAttributeSet* GetAuraAttributeSet(TSubclassOf<UAttributeSet> AttributeSetClass) const;
};
