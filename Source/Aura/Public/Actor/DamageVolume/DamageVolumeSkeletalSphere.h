// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "DamageVolumeBase.h"
#include "DamageVolumeSkeletalSphere.generated.h"

UCLASS()
class AURA_API ADamageVolumeSkeletalSphere : public ADamageVolumeBase
{
	GENERATED_BODY()

public:
	ADamageVolumeSkeletalSphere(const FObjectInitializer& ObjectInitializer);
};
