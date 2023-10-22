// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FloatingDamageComponent.generated.h"

UCLASS()
class AURA_API UFloatingDamageComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetDamage(float Damage, bool bBlockedHit, bool bCriticalHit);
};
