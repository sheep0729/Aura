// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Marco.h"

// TODO 写一个通用的宏
#define TAG_NAME(TagType, TagSubName) TagType##_##TagSubName
#define TAG_NAME_Two(TagType, TagSubName1, TagSubName2) TagType##_##TagSubName1##_##TagSubName2

#define DECLARE_TAG(TagName) static FGameplayTag TagName

#define TAG_GETTER(TagType, TagSubName) \
	static const FGameplayTag& Get##TagType##Tag##TagSubName()       \
	{                                                             \
		return TAG_NAME(TagType, TagSubName); \
	}

#define TAG_GETTER_Two(TagType, TagSubName1, TagSubName2) \
	static const FGameplayTag& Get##TagType##Tag##TagSubName1##TagSubName2()       \
	{                                                             \
		return TAG_NAME_Two(TagType, TagSubName1, TagSubName2); \
	}

// Attribute

#define ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName) Attribute_##AttributeClass##_##AttributeName
#define DECLARE_ATTRIBUTE_TAG(AttributeClass, AttributeName) DECLARE_TAG(ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName))
#define DECLARE_VITAL_ATTRIBUTE_TAG(AttributeName) DECLARE_ATTRIBUTE_TAG(Vital, AttributeName)
#define DECLARE_PRIMARY_ATTRIBUTE_TAG(AttributeName) DECLARE_ATTRIBUTE_TAG(Primary, AttributeName)
#define DECLARE_SECONDARY_ATTRIBUTE_TAG(AttributeName) DECLARE_ATTRIBUTE_TAG(Secondary, AttributeName)
#define ATTRIBUTE_TAG_GETTER(AttributeClass, AttributeName)       \
	static const FGameplayTag& GetAttributeTag##AttributeName()   \
	{                                                             \
		return ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName); \
	}
#define VITAL_ATTRIBUTE_TAG_GETTER(AttributeName)  ATTRIBUTE_TAG_GETTER(Vital, AttributeName)
#define PRIMARY_ATTRIBUTE_TAG_GETTER(AttributeName) ATTRIBUTE_TAG_GETTER(Primary, AttributeName)
#define SECONDARY_ATTRIBUTE_TAG_GETTER(AttributeName) ATTRIBUTE_TAG_GETTER(Secondary, AttributeName)

// Input

#define INPUT_TAG_NAME(InputName) InputTag_##InputName
#define DECLARE_INPUT_TAG(InputName) DECLARE_TAG(INPUT_TAG_NAME(InputName));
#define INPUT_TAG_GETTER(InputName)                     \
	static const FGameplayTag& GetInputTag##InputName() \
	{                                                   \
		return INPUT_TAG_NAME(InputName);               \
	}

// Effect

#define EFFECT_TAG_NAME(EffectName) Effect_##EffectName
#define DECLARE_EFFECT_TAG(EffectName) DECLARE_TAG(EFFECT_TAG_NAME(EffectName))
#define EFFECT_TAG_GETTER(EffectName)                     \
	static const FGameplayTag& GetEffectTag##EffectName() \
	{                                                     \
		return EFFECT_TAG_NAME(EffectName);               \
	}

// Damage

#define DAMAGE_TYPE_TAG_NAME(DamageTypeName) DamageType_##DamageTypeName
#define DECLARE_DAMAGE_TYPE_TAG(DamageTypeName) DECLARE_TAG(DAMAGE_TYPE_TAG_NAME(DamageTypeName))
#define DAMAGE_TYPE_TAG_GETTER(DamageTypeName)                     \
static const FGameplayTag& GetDamageTypeTag##DamageTypeName()      \
{                                                                  \
	return DAMAGE_TYPE_TAG_NAME(DamageTypeName);                   \
}

// Ability

#define ABILITY_TAG_NAME(AbilityName) Ability_##AbilityName
#define DECLARE_ABILITY_TAG(AbilityName) DECLARE_TAG(ABILITY_TAG_NAME(AbilityName))
#define ABILITY_TAG_GETTER(AbilityName)                      \
static const FGameplayTag& GetAbilityTag##AbilityName()      \
{                                                            \
	return ABILITY_TAG_NAME(AbilityName);                    \
}

struct FAuraGameplayTags
{
	static void InitializeAuraGameplayTags();

	VITAL_ATTRIBUTE_TAG_GETTER(Health);
	VITAL_ATTRIBUTE_TAG_GETTER(Mana);

	PRIMARY_ATTRIBUTE_TAG_GETTER(Strength);
	PRIMARY_ATTRIBUTE_TAG_GETTER(Intelligence);
	PRIMARY_ATTRIBUTE_TAG_GETTER(Resilience);
	PRIMARY_ATTRIBUTE_TAG_GETTER(Vigor);

	SECONDARY_ATTRIBUTE_TAG_GETTER(Armor);
	SECONDARY_ATTRIBUTE_TAG_GETTER(ArmorPenetration);
	SECONDARY_ATTRIBUTE_TAG_GETTER(BlockChance);
	SECONDARY_ATTRIBUTE_TAG_GETTER(CriticalHitChance);
	SECONDARY_ATTRIBUTE_TAG_GETTER(CriticalHitDamage);
	SECONDARY_ATTRIBUTE_TAG_GETTER(CriticalHitResistance);
	SECONDARY_ATTRIBUTE_TAG_GETTER(HealthRegeneration);
	SECONDARY_ATTRIBUTE_TAG_GETTER(ManaRegeneration);
	SECONDARY_ATTRIBUTE_TAG_GETTER(MaxHealth);
	SECONDARY_ATTRIBUTE_TAG_GETTER(MaxMana);
	SECONDARY_ATTRIBUTE_TAG_GETTER(FireResistance);
	SECONDARY_ATTRIBUTE_TAG_GETTER(LightningResistance);
	SECONDARY_ATTRIBUTE_TAG_GETTER(ArcaneResistance);
	SECONDARY_ATTRIBUTE_TAG_GETTER(PhysicalResistance);

	static const TArray<FGameplayTag>& GetPrimaryAttributeTags();
	static const TArray<FGameplayTag>& GetSecondaryAttributeTags();
	static const TArray<FGameplayTag>& GetVitalAttributeTags();
	static const TMap<FGameplayTag, FGameplayAttribute>& GetAttributeMap();

	INPUT_TAG_GETTER(LMB);
	INPUT_TAG_GETTER(RMB);
	INPUT_TAG_GETTER(1);
	INPUT_TAG_GETTER(2);
	INPUT_TAG_GETTER(3);
	INPUT_TAG_GETTER(4);
	INPUT_TAG_GETTER(Move);
	INPUT_TAG_GETTER(Shift);

	EFFECT_TAG_GETTER(Damage);
	EFFECT_TAG_GETTER(HitReact);

	DAMAGE_TYPE_TAG_GETTER(Fire);
	DAMAGE_TYPE_TAG_GETTER(Lightning);
	DAMAGE_TYPE_TAG_GETTER(Arcane);
	DAMAGE_TYPE_TAG_GETTER(Physical);

	static const TMap<FGameplayTag, FGameplayTag>& GetDamageToResistanceMap();

	ABILITY_TAG_GETTER(Attack);

	TAG_GETTER(CombatSocket, Weapon);
	TAG_GETTER(CombatSocket, LeftHand);
	TAG_GETTER(CombatSocket, RightHand);
	TAG_GETTER(CombatSocket, Tail);
	
	TAG_GETTER_Two(Montage, Attack, 1);
	TAG_GETTER_Two(Montage, Attack, 2);
	TAG_GETTER_Two(Montage, Attack, 3);
	TAG_GETTER_Two(Montage, Attack, 4);
protected:
	DECLARE_VITAL_ATTRIBUTE_TAG(Health);
	DECLARE_VITAL_ATTRIBUTE_TAG(Mana);

	DECLARE_PRIMARY_ATTRIBUTE_TAG(Strength);
	DECLARE_PRIMARY_ATTRIBUTE_TAG(Intelligence);
	DECLARE_PRIMARY_ATTRIBUTE_TAG(Resilience);
	DECLARE_PRIMARY_ATTRIBUTE_TAG(Vigor);

	DECLARE_SECONDARY_ATTRIBUTE_TAG(Armor);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(ArmorPenetration);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(BlockChance);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(CriticalHitChance);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(CriticalHitDamage);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(CriticalHitResistance);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(HealthRegeneration);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(ManaRegeneration);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(MaxHealth);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(MaxMana);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(FireResistance);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(LightningResistance);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(ArcaneResistance);
	DECLARE_SECONDARY_ATTRIBUTE_TAG(PhysicalResistance);

	DECLARE_INPUT_TAG(LMB);
	DECLARE_INPUT_TAG(RMB);
	DECLARE_INPUT_TAG(1);
	DECLARE_INPUT_TAG(2);
	DECLARE_INPUT_TAG(3);
	DECLARE_INPUT_TAG(4);
	DECLARE_INPUT_TAG(Move);
	DECLARE_INPUT_TAG(Shift);

	DECLARE_EFFECT_TAG(Damage);
	DECLARE_EFFECT_TAG(HitReact);

	DECLARE_DAMAGE_TYPE_TAG(Fire);
	DECLARE_DAMAGE_TYPE_TAG(Lightning);
	DECLARE_DAMAGE_TYPE_TAG(Arcane);
	DECLARE_DAMAGE_TYPE_TAG(Physical);

	DECLARE_ABILITY_TAG(Attack);

	DECLARE_TAG(TAG_NAME(CombatSocket, Weapon));
	DECLARE_TAG(TAG_NAME(CombatSocket, LeftHand));
	DECLARE_TAG(TAG_NAME(CombatSocket, RightHand));
	DECLARE_TAG(TAG_NAME(CombatSocket, Tail));

	DECLARE_TAG(TAG_NAME_Two(Montage, Attack, 1));
	DECLARE_TAG(TAG_NAME_Two(Montage, Attack, 2));
	DECLARE_TAG(TAG_NAME_Two(Montage, Attack, 3));
	DECLARE_TAG(TAG_NAME_Two(Montage, Attack, 4));
};
