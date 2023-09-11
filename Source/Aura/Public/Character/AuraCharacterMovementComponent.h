// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AuraCharacterMovementComponent.generated.h"


UCLASS()
class AURA_API UAuraCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UAuraCharacterMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
