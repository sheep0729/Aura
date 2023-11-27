#include "Actor/DamageVolume/DamageVolumeBase.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

FName ADamageVolumeBase::DamageCauserMeshName{"DamageCauserMesh"};
FName ADamageVolumeBase::DamageVolumeName{"DamageVolume"};

ADamageVolumeBase::ADamageVolumeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DamageCauserMesh = CreateDefaultSubobject<UMeshComponent>(DamageCauserMeshName);
	DamageVolume = CreateDefaultSubobject<UShapeComponent>(DamageVolumeName);

	SetRootComponent(DamageCauserMesh);
}

void ADamageVolumeBase::UpdateDefaultObject()
{
	if (const auto CDO = Cast<ADamageVolumeBase>(GetClass()->GetDefaultObject()); IsValid(CDO))
	{
		if (IsValid(CDO->GetDamageVolume()))
		{
			if (const auto Sphere = Cast<USphereComponent>(CDO->GetDamageVolume()))
			{
				CDO->CollisionShape = FCollisionShape::MakeSphere(Sphere->GetScaledSphereRadius());
			}
			else if (const auto Capsule = Cast<UCapsuleComponent>(CDO->GetDamageVolume()))
			{
				CDO->CollisionShape = FCollisionShape::MakeCapsule(Capsule->GetScaledCapsuleRadius(), Capsule->GetScaledCapsuleHalfHeight());
			}
			else if (const auto Box = Cast<UBoxComponent>(CDO->GetDamageVolume()))
			{
				CDO->CollisionShape = FCollisionShape::MakeBox(Box->GetScaledBoxExtent());
			}

			CDO->CollisionShapeRelativeTransform = CDO->GetDamageVolume()->GetRelativeTransform();
		}
	}
}

void ADamageVolumeBase::PostCDOCompiled(const FPostCDOCompiledContext& Context)
{
	Super::PostCDOCompiled(Context);

	UpdateDefaultObject();
}
