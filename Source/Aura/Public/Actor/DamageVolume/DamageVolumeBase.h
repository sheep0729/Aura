// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Marco.h"
#include "GameFramework/Actor.h"
#include "DamageVolumeBase.generated.h"

UCLASS(Abstract) // 注意：有 Abstract 的 UProperty ，不标记 Abstract 会崩溃
class AURA_API ADamageVolumeBase : public AActor
{
	GENERATED_BODY()

public:
	ADamageVolumeBase(const FObjectInitializer& ObjectInitializer);

	void UpdateDefaultObject();
	virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;

	VALUE_GETTER(DamageCauserMesh);
	VALUE_GETTER(DamageVolume);
	VALUE_GETTER(CollisionShape);
	VALUE_GETTER(CollisionShapeRelativeTransform);

protected:
	static FName DamageCauserMeshName;
	static FName DamageVolumeName;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UMeshComponent* DamageCauserMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UShapeComponent* DamageVolume;

	FCollisionShape CollisionShape;

	FTransform CollisionShapeRelativeTransform;
};
