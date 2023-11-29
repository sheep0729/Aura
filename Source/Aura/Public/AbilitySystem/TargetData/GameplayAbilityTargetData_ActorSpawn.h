#pragma once
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayAbilityTargetData_ActorSpawn.generated.h"

USTRUCT(BlueprintType)
struct AURA_API FGameplayAbilityTargetData_ActorSpawn : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

	FGameplayAbilityTargetData_ActorSpawn() {};
	FGameplayAbilityTargetData_ActorSpawn(const FTransform& Transform);
	
	virtual FTransform GetEndPointTransform() const override;
	
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

private:

	FTransform EndPointTransform;
};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_ActorSpawn> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_ActorSpawn>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};