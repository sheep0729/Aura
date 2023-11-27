// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Marco.h"
#include "UObject/Object.h"
#include "CurveTransform.generated.h"


class UCurveVector;

UCLASS()
class AURA_API UCurveTransform : public UObject
{
	GENERATED_BODY()

public:
	VALUE_GETTER(TranslationCurve);
	VALUE_GETTER(RotationVectorCurve);
	VALUE_GETTER(Scale3DCurve);

	UCurveTransform();

	FTransform GetTransform(float Time);
	void SetTransform(float Time, const FTransform& Transform);
	void Clear();

private:
	UPROPERTY(Instanced)
	UCurveVector* TranslationCurve;

	// 这种存储方式虽然可能会在插值时有问题，但一般的场景间隔应该很小
	UPROPERTY(Instanced)
	UCurveVector* RotationVectorCurve;

	UPROPERTY(Instanced)
	UCurveVector* Scale3DCurve;

	void Init(UCurveVector*& CurveVector, FName Name);

	void AddVector(UCurveVector*& CurveVector, float Time, const FVector& Vector);
};
