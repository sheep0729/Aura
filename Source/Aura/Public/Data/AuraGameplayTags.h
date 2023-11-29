// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

#define TAG_GETTER(TagName) \
	static FGameplayTag GetTag_##TagName() \
	{                                             \
		return TagName; \
	}

struct FAuraGameplayTags
{
	// static void InitializeAuraGameplayTags();

	static const TArray<FGameplayTag>& GetPrimaryAttributeTags();
	static const TArray<FGameplayTag>& GetSecondaryAttributeTags();
	static const TArray<FGameplayTag>& GetVitalAttributeTags();
	static const TMap<FGameplayTag, FGameplayAttribute>& GetAttributeMap();
	static const TMap<FGameplayTag, FGameplayTag>& GetDamageToResistanceMap();

	static const FNativeGameplayTag Attribute_Vital_Health;
	static const FNativeGameplayTag Attribute_Vital_Mana;
	static const FNativeGameplayTag Attribute_Primary_Strength;
	static const FNativeGameplayTag Attribute_Primary_Intelligence;
	static const FNativeGameplayTag Attribute_Primary_Resilience;
	static const FNativeGameplayTag Attribute_Primary_Vigor;
	static const FNativeGameplayTag Attribute_Secondary_Armor;
	static const FNativeGameplayTag Attribute_Secondary_ArmorPenetration;
	static const FNativeGameplayTag Attribute_Secondary_BlockChance;
	static const FNativeGameplayTag Attribute_Secondary_CriticalHitChance;
	static const FNativeGameplayTag Attribute_Secondary_CriticalHitDamage;
	static const FNativeGameplayTag Attribute_Secondary_CriticalHitResistance;
	static const FNativeGameplayTag Attribute_Secondary_HealthRegeneration;
	static const FNativeGameplayTag Attribute_Secondary_ManaRegeneration;
	static const FNativeGameplayTag Attribute_Secondary_MaxHealth;
	static const FNativeGameplayTag Attribute_Secondary_MaxMana;
	static const FNativeGameplayTag Attribute_Secondary_FireResistance;
	static const FNativeGameplayTag Attribute_Secondary_LightningResistance;
	static const FNativeGameplayTag Attribute_Secondary_ArcaneResistance;
	static const FNativeGameplayTag Attribute_Secondary_PhysicalResistance;
	static const FNativeGameplayTag Input_LMB;
	static const FNativeGameplayTag Input_RMB;
	static const FNativeGameplayTag Input_1;
	static const FNativeGameplayTag Input_2;
	static const FNativeGameplayTag Input_3;
	static const FNativeGameplayTag Input_4;
	static const FNativeGameplayTag Input_Move;
	static const FNativeGameplayTag Input_Shift;
	static const FNativeGameplayTag Effect_Damage;
	static const FNativeGameplayTag Effect_HitReact;
	static const FNativeGameplayTag Damage_Fire;
	static const FNativeGameplayTag Damage_Lightning;
	static const FNativeGameplayTag Damage_Arcane;
	static const FNativeGameplayTag Damage_Physical;
	static const FNativeGameplayTag Ability_Attack;
	static const FNativeGameplayTag Ability_Summon;
	static const FNativeGameplayTag CombatSocket_Weapon;
	static const FNativeGameplayTag CombatSocket_LeftHand;
	static const FNativeGameplayTag CombatSocket_RightHand;
	static const FNativeGameplayTag CombatSocket_Tail;
	static const FNativeGameplayTag Montage_Attack_1;
	static const FNativeGameplayTag Montage_Attack_2;
	static const FNativeGameplayTag Montage_Attack_3;
	static const FNativeGameplayTag Montage_Attack_4;
};
