#include "Actor/DamageVolume/DamageVolumeSkeletalBox.h"
#include "Components/BoxComponent.h"

ADamageVolumeSkeletalBox::ADamageVolumeSkeletalBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer
	        .SetDefaultSubobjectClass(DamageCauserMeshName, USkeletalMeshComponent::StaticClass())
	        .SetDefaultSubobjectClass(DamageVolumeName, UBoxComponent::StaticClass()))
{
}
