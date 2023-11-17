// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Marco.h"
#include "Animation/AnimMetaData.h"
#include "AMD_Montage.generated.h"

class UCurveVector;

UCLASS()
class AURA_API UAMD_Montage : public UAnimMetaData
{
	GENERATED_BODY()

public:
	VALUE_GETTER(DamageOrigins);

	UAMD_Montage();

private:
	UPROPERTY(Instanced)
	UCurveVector* DamageOrigins;
};
