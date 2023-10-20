#include "AbilitySystem/AuraAbilityType.h"

FAuraGameplayEffectContext::FAuraGameplayEffectContext()
	:bIsBlockHit(false)
{
}

UScriptStruct* FAuraGameplayEffectContext::GetScriptStruct() const
{
	return StaticStruct();
}

bool FAuraGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	if (!Super::NetSerialize(Ar, Map, bOutSuccess))
	{
		return false;
	}

	uint8 RepBits = 0;
	if (Ar.IsSaving())
	{
		if (IsBlockHit())
		{
			RepBits |= 1 << 0;
		}

		if (IsCriticalHit())
		{
			RepBits |= 1 << 1;
		}
	}

	Ar.SerializeBits(&RepBits, 2);

	if (RepBits & 1)
	{
		Ar << bIsBlockHit;
	}

	if (RepBits & (1 << 1))
	{
		Ar << bIsCriticalHit;
	}

	return true;
}

FAuraGameplayEffectContext* FAuraGameplayEffectContext::Duplicate() const
{
	FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
	*NewContext = *this;
	if (GetHitResult())
	{
		// Does a deep copy of the hit result
		NewContext->AddHitResult(*GetHitResult(), true);
	}
	return NewContext;
}
