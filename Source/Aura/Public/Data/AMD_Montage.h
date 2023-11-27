// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Marco.h"
#include "Animation/AnimMetaData.h"
#include "AMD_Montage.generated.h"

class UCurveTransform;
class UCurveVector;

UCLASS()
class AURA_API UAMD_Montage : public UAnimMetaData
{
	GENERATED_BODY()

public:
	UAMD_Montage();

	VALUE_GETTER(DamageTransform)
private:
	UPROPERTY(Instanced)
	UCurveTransform* DamageTransform;
};
