// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "UObject/Interface.h"
#include "AuraAbilitySystemInterface.generated.h"

class UAuraAbilitySystemComponent;

UINTERFACE(MinimalAPI)
class UAuraAbilitySystemInterface : public UInterface
{
	GENERATED_BODY()
};

class AURA_API IAuraAbilitySystemInterface : public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	virtual UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent() const = 0;
};
