// Copyright Yang Dong


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::GetAbilityInputAction(const FGameplayTag& GameplayTag, bool bLogNotFound) const
{
	const auto& InputAction = AbilityInputActions.Find(GameplayTag);

	if (!InputAction)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for Tag [%s] on InputConfig [%s]"), *GameplayTag.ToString(), *GetNameSafe(this));
		return nullptr;
	}
	
	return *InputAction;
}
