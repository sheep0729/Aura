// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "DamageVolumeBase.h"
#include "DamageVolumeSkeletalBox.generated.h"

UCLASS()
class AURA_API ADamageVolumeSkeletalBox : public ADamageVolumeBase
{
	GENERATED_BODY()

public:
	ADamageVolumeSkeletalBox(const FObjectInitializer& ObjectInitializer);
};
