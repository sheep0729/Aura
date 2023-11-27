// Copyright Yang Dong


#include "Actor/DamageVolume/DamageVolumeSkeletalSphere.h"

#include "Components/SphereComponent.h"

ADamageVolumeSkeletalSphere::ADamageVolumeSkeletalSphere(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer
			.SetDefaultSubobjectClass(DamageCauserMeshName, USkeletalMeshComponent::StaticClass())
			.SetDefaultSubobjectClass(DamageVolumeName, USphereComponent::StaticClass()))
{
}

