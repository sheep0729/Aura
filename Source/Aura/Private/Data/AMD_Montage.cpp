// Copyright Yang Dong


#include "Data/AMD_Montage.h"

#include "Curves/CurveVector.h"

UAMD_Montage::UAMD_Montage()
{
	DamageOrigins = CreateDefaultSubobject<UCurveVector>("DamageOrigins");
	for (auto& Curve : DamageOrigins->FloatCurves)
	{
		Curve.PreInfinityExtrap = RCCE_Constant;
		Curve.PostInfinityExtrap = RCCE_Constant;
	}
}
