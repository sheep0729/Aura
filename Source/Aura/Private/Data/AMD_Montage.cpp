// Copyright Yang Dong


#include "Data/AMD_Montage.h"
#include "Data/CurveTransform.h"


UAMD_Montage::UAMD_Montage()
{
	DamageTransform = CreateDefaultSubobject<UCurveTransform>("DamageTransform");
}
