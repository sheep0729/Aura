#include "AbilitySystem/TargetData/GameplayAbilityTargetData_ActorSpawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameplayAbilityTargetData_ActorSpawn)


FGameplayAbilityTargetData_ActorSpawn::FGameplayAbilityTargetData_ActorSpawn(const FTransform& Transform)
{
	EndPointTransform = Transform;
}

FTransform FGameplayAbilityTargetData_ActorSpawn::GetEndPointTransform() const
{
	return EndPointTransform;
}

bool FGameplayAbilityTargetData_ActorSpawn::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << EndPointTransform;
	bOutSuccess = true;
	return true;
}
