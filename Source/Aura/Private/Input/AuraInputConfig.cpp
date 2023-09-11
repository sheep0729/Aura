// Copyright Yang Dong


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::GetAbilityInputAction(const FGameplayTag& GameplayTag, bool bLogNotFound) const
{
	return GetInputAction(AbilityInputActions, GameplayTag, bLogNotFound);
}

const UInputAction* UAuraInputConfig::GetNativeInputAction(const FGameplayTag& GameplayTag, bool bLogNotFound) const
{
	return GetInputAction(NativeInputActions, GameplayTag, bLogNotFound);
}

const UInputAction* UAuraInputConfig::GetInputAction(const TMap<FGameplayTag, UInputAction*>& InputActions, const FGameplayTag& GameplayTag,
                                                     bool bLogNotFound) const
{
	const auto& InputAction = InputActions.Find(GameplayTag);

	if (!InputAction)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for Tag [%s] on InputConfig [%s]"), *GameplayTag.ToString(), *GetNameSafe(this));
		return nullptr;
	}

	return *InputAction;
}
