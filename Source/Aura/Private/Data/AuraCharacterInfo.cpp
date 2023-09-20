// Copyright Yang Dong


#include "Data/AuraCharacterInfo.h"
#include "UObject/ObjectSaveContext.h"
#include "Abilities/GameplayAbility.h"

const FAuraCharacterInfo& UAuraCharacterData::GetCharacterInfo(const EAuraCharacterClass CharacterClass)
{
    if (const auto CharacterClassPtr = CharacterInfoMap.Find(CharacterClass))
    {
        return *CharacterClassPtr;
    }

    return DefaultCharacterInfo;
}

void UAuraCharacterData::PreSave(FObjectPreSaveContext SaveContext)
{
    Super::PreSave(SaveContext);

    FillDefaultValues();
}

void UAuraCharacterData::PostLoad()
{
    Super::PostLoad();

    FillDefaultValues();
}

void UAuraCharacterData::FillDefaultValues()
{
    for (auto& Pair : CharacterInfoMap) 
    {
        auto& CharacterInfo = Pair.Value;
        FillDefaultValues(CharacterInfo);
    }
}

void UAuraCharacterData::FillDefaultValues(FAuraCharacterInfo& Data)
{
    for (int32 i = 0; i < DefaultCharacterInfo.GetAttributeEffects().Num(); i += 1)
    {
        if (i >= Data.GetAttributeEffects().Num())
        {
            Data.GetAttributeEffects().Add(DefaultCharacterInfo.GetAttributeEffects()[i]);
        }
        else if (!IsValid(Data.GetAttributeEffects()[i]))
        {
            Data.GetAttributeEffects()[i] = DefaultCharacterInfo.GetAttributeEffects()[i];
        }
    }

    for(const auto Ability : DefaultCharacterInfo.GetAbilities()) 
    {
        if (Data.GetAbilities().Find(Ability) == INDEX_NONE) 
        {
            Data.GetAbilities().Add(Ability);
        }
    }
}
