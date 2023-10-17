// Copyright Yang Dong


#include "Game/AuraGameStateBase.h"
#include "Data/AuraCharacterInfo.h"

const FAuraCharacterInfo& AAuraGameStateBase::GetCharacterInfo(const EAuraCharacterClass CharacterClass) const
{
    return CharacterData->GetCharacterInfo(CharacterClass);
}

const UCurveTable* AAuraGameStateBase::GetDamageCalculationCoefficients() const
{
    return CharacterData->GetDamageCalculationCoefficients();
}
