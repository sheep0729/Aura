// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Marco.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

class UInputAction;

UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* GetAbilityInputAction(const FGameplayTag& GameplayTag, bool bLogNotFound = false) const;

	CONST_REF_GETTER(AbilityInputActions);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, UInputAction*> AbilityInputActions;
};
