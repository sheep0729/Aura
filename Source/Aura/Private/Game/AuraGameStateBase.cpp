// Copyright Yang Dong


#include "Game/AuraGameStateBase.h"
#include "Data/AuraCharacterInfo.h"

const FAuraCharacterInfo& AAuraGameStateBase::GetCharacterInfo(EAuraCharacterClass CharacterClass) const
{
    return CharacterData->GetCharacterInfo(CharacterClass);
}
