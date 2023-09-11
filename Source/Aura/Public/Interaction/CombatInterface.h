// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:

	virtual int32 GetActorLevel() PURE_VIRTUAL(ICombatInterface::GetActorLevel, return -1;);
	virtual FVector GetWeaponFireSocketLocation() PURE_VIRTUAL(ICombatInterface::GetWeaponFireSocketLocation, return FVector(););

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetFacingTarget(const FVector& TargetLocation);
};
