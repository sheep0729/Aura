#pragma once

#include "GameplayEffectTypes.h"
#include "Marco.h"
#include "AuraAbilityType.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	FAuraGameplayEffectContext();

	VALUE_GETTER_FUNC_NAME(bIsBlockHit, IsBlockHit);
	SETTER_FUNC_NAME(bIsBlockHit, SetIsBlockHit);

	VALUE_GETTER_FUNC_NAME(bIsCriticalHit, IsCriticalHit);
	SETTER_FUNC_NAME(bIsCriticalHit, SetIsCriticalHit);

	virtual UScriptStruct* GetScriptStruct() const override;
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
	virtual FAuraGameplayEffectContext* Duplicate() const override;
	
protected:

private:
	UPROPERTY()
	bool bIsBlockHit;

	UPROPERTY()
	bool bIsCriticalHit;
};


template<>
struct TStructOpsTypeTraits< FAuraGameplayEffectContext > : public TStructOpsTypeTraitsBase2< FAuraGameplayEffectContext >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};