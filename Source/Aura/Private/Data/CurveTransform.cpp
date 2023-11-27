// Copyright Yang Dong


#include "Data/CurveTransform.h"

#include "Curves/CurveVector.h"

UCurveTransform::UCurveTransform()
{
	Init(RotationVectorCurve, "DamageOriginRotation");
	Init(TranslationCurve, "DamageOriginTranslation");
	Init(Scale3DCurve, "DamageOriginScale3D");
}

FTransform UCurveTransform::GetTransform(float Time)
{
	const FVector& Translation = TranslationCurve->GetVectorValue(Time);
	const FQuat& Rotation = FQuat::MakeFromRotationVector(RotationVectorCurve->GetVectorValue(Time));
	const FVector& Scale3D = Scale3DCurve->GetVectorValue(Time);

	return FTransform{Rotation, Translation, Scale3D};
}

void UCurveTransform::SetTransform(float Time, const FTransform& Transform)
{
	const FVector& Translation = Transform.GetTranslation();
	const FVector& RotationVector = Transform.GetRotation().ToRotationVector();
	const FVector& Scale3D = Transform.GetScale3D();

	AddVector(TranslationCurve, Time, Translation);
	AddVector(RotationVectorCurve, Time, RotationVector);
	AddVector(Scale3DCurve, Time, Scale3D);
}

void UCurveTransform::Clear()
{
	TranslationCurve->ResetCurve();
	RotationVectorCurve->ResetCurve();
	Scale3DCurve->ResetCurve();
}

void UCurveTransform::Init(UCurveVector*& CurveVector, FName Name)
{
	CurveVector = CreateDefaultSubobject<UCurveVector>(Name);
	for (auto& Curve : CurveVector->FloatCurves)
	{
		Curve.PreInfinityExtrap = RCCE_Constant;
		Curve.PostInfinityExtrap = RCCE_Constant;
	}
}

void UCurveTransform::AddVector(UCurveVector*& CurveVector, float Time, const FVector& Vector)
{
	for (int i = 0; i < 3; i++)
	{
		CurveVector->FloatCurves[i].AddKey(Time, Vector[i]);
	}
}