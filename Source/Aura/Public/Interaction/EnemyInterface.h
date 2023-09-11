// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class AURA_API IEnemyInterface
{
	GENERATED_BODY()

public:

	virtual void HighlightActor(UPrimitiveComponent* TouchedComponent) = 0;
	virtual void UnhighlightActor(UPrimitiveComponent* TouchedComponent) = 0;
};
