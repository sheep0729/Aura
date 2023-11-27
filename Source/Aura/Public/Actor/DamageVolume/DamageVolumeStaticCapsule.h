// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "DamageVolumeBase.h"
#include "DamageVolumeStaticCapsule.generated.h"

UCLASS()
class AURA_API ADamageVolumeStaticCapsule : public ADamageVolumeBase
{
	GENERATED_BODY()

public:
	ADamageVolumeStaticCapsule(const FObjectInitializer& ObjectInitializer);
};
