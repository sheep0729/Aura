// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemy.generated.h"

UINTERFACE(MinimalAPI)
class UEnemy : public UInterface
{
	GENERATED_BODY()
};

class AURA_API IEnemy
{
	GENERATED_BODY()

public:

	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
