#include "Actor/DamageVolume/DamageVolumeStaticCapsule.h"
#include "Components/CapsuleComponent.h"

ADamageVolumeStaticCapsule::ADamageVolumeStaticCapsule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer
	        .SetDefaultSubobjectClass(DamageCauserMeshName, UStaticMeshComponent::StaticClass())
	        .SetDefaultSubobjectClass(DamageVolumeName, UCapsuleComponent::StaticClass()))
{
}
