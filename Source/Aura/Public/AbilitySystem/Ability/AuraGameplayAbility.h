// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Marco.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	CONST_REF_GETTER(StartupInputTag)

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Custom|Input")
	FGameplayTag StartupInputTag;
};
