// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraEnhancedInputComponent.generated.h"

class UAuraInputConfig;

UCLASS()
class AURA_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <typename UserClass, typename PressedFuncType, typename HoldingFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, HoldingFuncType HoldingFunc,
	                        ReleasedFuncType ReleasedFunc);
};

template <typename UserClass, typename PressedFuncType, typename HoldingFuncType, typename ReleasedFuncType>
void UAuraEnhancedInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, HoldingFuncType HoldingFunc,
                                                     ReleasedFuncType ReleasedFunc)
{
	check(InputConfig);

	for (const auto& Pair : InputConfig->GetAbilityInputActions())
	{
		const auto& InputTag = Pair.Key;
		const auto& InputAction = Pair.Value;

		if (InputTag.IsValid() && InputAction)
		{
			if (PressedFunc)
			{
				BindAction(InputAction, ETriggerEvent::Started, Object, PressedFunc, InputTag);
			}

			if (HoldingFunc)
			{
				BindAction(InputAction, ETriggerEvent::Triggered, Object, HoldingFunc, InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, InputTag);
			}
		}
	}
}
