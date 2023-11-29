// Copyright Yang Dong

#include "Data/AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

const TArray<FGameplayTag>& FAuraGameplayTags::GetVitalAttributeTags()
{
	static const TArray<FGameplayTag> VitalAttributeTags{
		Attribute_Vital_Health,
		Attribute_Vital_Mana
	};

	return VitalAttributeTags;
}

const TArray<FGameplayTag>& FAuraGameplayTags::GetPrimaryAttributeTags()
{
	static const TArray<FGameplayTag> PrimaryAttributeTags = {
		Attribute_Primary_Strength,
		Attribute_Primary_Intelligence,
		Attribute_Primary_Resilience,
		Attribute_Primary_Vigor,
	};

	return PrimaryAttributeTags;
}

const TArray<FGameplayTag>& FAuraGameplayTags::GetSecondaryAttributeTags()
{
	static const TArray<FGameplayTag> SecondaryAttributeTags{
		Attribute_Secondary_Armor,
		Attribute_Secondary_ArmorPenetration,
		Attribute_Secondary_BlockChance,
		Attribute_Secondary_CriticalHitChance,
		Attribute_Secondary_CriticalHitDamage,
		Attribute_Secondary_CriticalHitResistance,
		Attribute_Secondary_HealthRegeneration,
		Attribute_Secondary_ManaRegeneration,
		Attribute_Secondary_MaxHealth,
		Attribute_Secondary_MaxMana,
		Attribute_Secondary_FireResistance,
		Attribute_Secondary_LightningResistance,
		Attribute_Secondary_ArcaneResistance,
		Attribute_Secondary_PhysicalResistance,
	};

	return SecondaryAttributeTags;
}


const TMap<FGameplayTag, FGameplayAttribute>& FAuraGameplayTags::GetAttributeMap()
{
	static const TMap<FGameplayTag, FGameplayAttribute> AttributeMap{
		{Attribute_Vital_Health, UAuraAttributeSet::GetHealthAttribute()},
		{Attribute_Vital_Mana, UAuraAttributeSet::GetManaAttribute()},

		{Attribute_Primary_Strength, UAuraAttributeSet::GetStrengthAttribute()},
		{Attribute_Primary_Intelligence, UAuraAttributeSet::GetIntelligenceAttribute()},
		{Attribute_Primary_Resilience, UAuraAttributeSet::GetResilienceAttribute()},
		{Attribute_Primary_Vigor, UAuraAttributeSet::GetVigorAttribute()},

		{Attribute_Secondary_Armor, UAuraAttributeSet::GetArmorAttribute()},
		{Attribute_Secondary_ArmorPenetration, UAuraAttributeSet::GetArmorPenetrationAttribute()},
		{Attribute_Secondary_BlockChance, UAuraAttributeSet::GetBlockChanceAttribute()},
		{Attribute_Secondary_CriticalHitChance, UAuraAttributeSet::GetCriticalHitChanceAttribute()},
		{Attribute_Secondary_CriticalHitDamage, UAuraAttributeSet::GetCriticalHitDamageAttribute()},
		{Attribute_Secondary_CriticalHitResistance, UAuraAttributeSet::GetCriticalHitResistanceAttribute()},
		{Attribute_Secondary_HealthRegeneration, UAuraAttributeSet::GetHealthRegenerationAttribute()},
		{Attribute_Secondary_ManaRegeneration, UAuraAttributeSet::GetManaRegenerationAttribute()},
		{Attribute_Secondary_MaxHealth, UAuraAttributeSet::GetMaxHealthAttribute()},
		{Attribute_Secondary_MaxMana, UAuraAttributeSet::GetMaxManaAttribute()},
		{Attribute_Secondary_FireResistance, UAuraAttributeSet::GetFireResistanceAttribute()},
		{Attribute_Secondary_LightningResistance, UAuraAttributeSet::GetLightningResistanceAttribute()},
		{Attribute_Secondary_ArcaneResistance, UAuraAttributeSet::GetArcaneResistanceAttribute()},
		{Attribute_Secondary_PhysicalResistance, UAuraAttributeSet::GetPhysicalResistanceAttribute()}
	};

	return AttributeMap;
}

// 伤害类型和对应的护甲类型
const TMap<FGameplayTag, FGameplayTag>& FAuraGameplayTags::GetDamageToResistanceMap()
{
	static TMap<FGameplayTag, FGameplayTag> DamageTypeMap{
		{Damage_Fire, Attribute_Secondary_FireResistance},
		{Damage_Lightning, Attribute_Secondary_LightningResistance},
		{Damage_Arcane, Attribute_Secondary_ArcaneResistance},
		{Damage_Physical, Attribute_Secondary_PhysicalResistance},
	};

	return DamageTypeMap;
}

const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Vital_Health, "Attribute.Vital.Health",
                                     "Amount of damage a player can take before death");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Vital_Mana, "Attribute.Vital.Mana", "");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Primary_Strength, "Attribute.Primary.Strength", "Increases physical damage");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Primary_Intelligence, "Attribute.Primary.Intelligence",
                                     "Increases armor and armor pentration");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Primary_Resilience, "Attribute.Primary.Resilience",
                                     "Increases armor and armor pentration");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Primary_Vigor, "Attribute.Primary.Vigor", "Increases health");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_Armor, "Attribute.Secondary.Armor",
                                     "Reduces damage taken, improves block chance");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_ArmorPenetration, "Attribute.Secondary.ArmorPenetration",
                                     "Ignore percentage of enemy Armor, increases crictical hit damage");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_BlockChance, "Attribute.Secondary.BlockChance",
                                     "Chance to cut incoming damage in half");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_CriticalHitChance, "Attribute.Secondary.CriticalHitChance",
                                     "Chance to double damage plus crictical hit bonus");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_CriticalHitDamage, "Attribute.Secondary.CriticalHitDamage",
                                     "Bonus damage added when a crictical hit is scored");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_CriticalHitResistance, "Attribute.Secondary.CriticalHitResistance",
                                     "Reduces crictical hit chance of attacking enemies");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_HealthRegeneration, "Attribute.Secondary.HealthRegeneration",
                                     "Amount of health regenerated every second");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_ManaRegeneration, "Attribute.Secondary.ManaRegeneration",
                                     "Amount of mana regenerated every second");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_MaxHealth, "Attribute.Secondary.MaxHealth",
                                     "Maxium amount of health obtainable");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_MaxMana, "Attribute.Secondary.MaxMana", "Maxium amount of mana obtainable");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_FireResistance, "Attribute.Secondary.FireResistance",
                                     "Resistance to Fire Damage");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_LightningResistance, "Attribute.Secondary.LightningResistance",
                                     "Resistance to Lightning Damage");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_ArcaneResistance, "Attribute.Secondary.ArcaneResistance",
                                     "Resistance to Arcane Damage");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Attribute_Secondary_PhysicalResistance, "Attribute.Secondary.PhysicalResistance",
                                     "Resistance to Physical Damage");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Input_LMB, "Input.LMB", "Input Tag for Left Mouse Button");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Input_RMB, "Input.RMB", "Input Tag for Right Mouse Button");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Input_1, "Input.1", "Input Tag for 1 Key");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Input_2, "Input.2", "Input Tag for 2 Key");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Input_3, "Input.3", "Input Tag for 3 Key");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Input_4, "Input.4", "Input Tag for 4 Key");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Input_Move, "Input.Move", "Input Tag for Move");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Input_Shift, "Input.Shift", "Input Tag for Shift Key");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Effect_Damage, "Effect.Damage", "");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Effect_HitReact, "Effect.HitReact", "Tag granted when reacting to hit");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Damage_Fire, "Damage.Fire", "Fire Damage Tag");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Damage_Lightning, "Damage.Lightning", "Lightning Damage Tag");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Damage_Arcane, "Damage.Arcane", "Arcane Damage Tag");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Damage_Physical, "Damage.Physical", "Physical Damage Tag");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Ability_Attack, "Ability.Attack", "Attack Ability Tag");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Ability_Summon, "Ability.Summon", "Attack Summon Tag");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::CombatSocket_Weapon, "CombatSocket.Weapon", "Weapon");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::CombatSocket_LeftHand, "CombatSocket.LeftHand", "LeftHand");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::CombatSocket_RightHand, "CombatSocket.RightHand", "RightHand");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::CombatSocket_Tail, "CombatSocket.Tail", "Tail");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Montage_Attack_1, "Montage.Attack.1", "Attack 1");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Montage_Attack_2, "Montage.Attack.2", "Attack 2");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Montage_Attack_3, "Montage.Attack.3", "Attack 3");
const UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::Montage_Attack_4, "Montage.Attack.4", "Attack 4");
