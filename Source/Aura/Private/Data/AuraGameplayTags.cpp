// Copyright Yang Dong


#include "Data/AuraGameplayTags.h"

#include "GameplayTagsManager.h"
#include "AbilitySystem/AuraAttributeSet.h"

#define IMPLEMENT_TAG(ClassName, TagName) FGameplayTag ClassName::TagName = FGameplayTag::EmptyTag;

// Attribute Tags（Tag 关联 Attribute） TODO 如果没有什么实际用途的话应该考虑删掉

#define IMPLEMENT_ATTRIBUTE_TAG(ClassName, AttributeClass, AttributeName) IMPLEMENT_TAG(ClassName, ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName))
#define IMPLEMENT_VITAL_ATTRIBUTE_TAG(ClassName, AttributeName) IMPLEMENT_ATTRIBUTE_TAG(ClassName, Vital, AttributeName)
#define IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(ClassName, AttributeName) IMPLEMENT_ATTRIBUTE_TAG(ClassName, Primary, AttributeName)
#define IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(ClassName, AttributeName) IMPLEMENT_ATTRIBUTE_TAG(ClassName, Secondary, AttributeName)

IMPLEMENT_VITAL_ATTRIBUTE_TAG(FAuraGameplayTags, Health);
IMPLEMENT_VITAL_ATTRIBUTE_TAG(FAuraGameplayTags, Mana);

IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(FAuraGameplayTags, Strength);
IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(FAuraGameplayTags, Intelligence);
IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(FAuraGameplayTags, Resilience);
IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(FAuraGameplayTags, Vigor);

IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, Armor);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, ArmorPenetration);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, BlockChance);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, CriticalHitChance);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, CriticalHitDamage);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, CriticalHitResistance);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, HealthRegeneration);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, ManaRegeneration);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, MaxHealth);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, MaxMana);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, FireResistance);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, LightningResistance);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, ArcaneResistance);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(FAuraGameplayTags, PhysicalResistance);

#define ATTRIBUTE_TAG_STR(AttributeClass, AttributeName) "Attributes." #AttributeClass "." #AttributeName

#define REQUEST_ATTRIBUTE_TAG(AttributeClass, AttributeName) \
	ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName) = FGameplayTag::RequestGameplayTag(FName(ATTRIBUTE_TAG_STR(AttributeClass, AttributeName)))
#define REQUEST_VITAL_ATTRIBUTE_TAG(AttributeName) REQUEST_ATTRIBUTE_TAG(Vital, AttributeName)
#define REQUEST_PRIMARY_ATTRIBUTE_TAG(AttributeName) REQUEST_ATTRIBUTE_TAG(Primary, AttributeName)

#define ADD_NATIVE_ATTRIBUTE_TAG(AttributeClass, AttributeName, TagDevComment) \
   ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName) = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(ATTRIBUTE_TAG_STR(AttributeClass, AttributeName)), TagDevComment);
#define ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(AttributeName, TagDevComment) ADD_NATIVE_ATTRIBUTE_TAG(Secondary, AttributeName, TagDevComment)

const TArray<FGameplayTag>& FAuraGameplayTags::GetPrimaryAttributeTags()
{
	static const TArray PrimaryAttributeTags = {
		GetAttributeTagStrength(),
		GetAttributeTagIntelligence(),
		GetAttributeTagResilience(),
		GetAttributeTagVigor()
	};

	return PrimaryAttributeTags;
}

const TArray<FGameplayTag>& FAuraGameplayTags::GetSecondaryAttributeTags()
{
	static const TArray SecondaryAttributeTags{
		GetAttributeTagArmor(),
		GetAttributeTagArmorPenetration(),
		GetAttributeTagBlockChance(),
		GetAttributeTagCriticalHitChance(),
		GetAttributeTagCriticalHitDamage(),
		GetAttributeTagCriticalHitResistance(),
		GetAttributeTagHealthRegeneration(),
		GetAttributeTagManaRegeneration(),
		GetAttributeTagMaxHealth(),
		GetAttributeTagMaxMana(),
		GetAttributeTagFireResistance(),
		GetAttributeTagLightningResistance(),
		GetAttributeTagArcaneResistance(),
		GetAttributeTagPhysicalResistance(),
	};

	return SecondaryAttributeTags;
}

const TArray<FGameplayTag>& FAuraGameplayTags::GetVitalAttributeTags()
{
	static const TArray VitalAttributeTags{
		GetAttributeTagHealth(),
		GetAttributeTagMana()
	};

	return VitalAttributeTags;
}

const TMap<FGameplayTag, FGameplayAttribute>& FAuraGameplayTags::GetAttributeMap()
{
	static const TMap<FGameplayTag, FGameplayAttribute> AttributeMap{
		{GetAttributeTagHealth(), UAuraAttributeSet::GetHealthAttribute()},
		{GetAttributeTagMana(), UAuraAttributeSet::GetManaAttribute()},

		{GetAttributeTagStrength(), UAuraAttributeSet::GetStrengthAttribute()},
		{GetAttributeTagIntelligence(), UAuraAttributeSet::GetIntelligenceAttribute()},
		{GetAttributeTagResilience(), UAuraAttributeSet::GetResilienceAttribute()},
		{GetAttributeTagVigor(), UAuraAttributeSet::GetVigorAttribute()},

		{GetAttributeTagArmor(), UAuraAttributeSet::GetArmorAttribute()},
		{GetAttributeTagArmorPenetration(), UAuraAttributeSet::GetArmorPenetrationAttribute()},
		{GetAttributeTagBlockChance(), UAuraAttributeSet::GetBlockChanceAttribute()},
		{GetAttributeTagCriticalHitChance(), UAuraAttributeSet::GetCriticalHitChanceAttribute()},
		{GetAttributeTagCriticalHitDamage(), UAuraAttributeSet::GetCriticalHitDamageAttribute()},
		{GetAttributeTagCriticalHitResistance(), UAuraAttributeSet::GetCriticalHitResistanceAttribute()},
		{GetAttributeTagHealthRegeneration(), UAuraAttributeSet::GetHealthRegenerationAttribute()},
		{GetAttributeTagManaRegeneration(), UAuraAttributeSet::GetManaRegenerationAttribute()},
		{GetAttributeTagMaxHealth(), UAuraAttributeSet::GetMaxHealthAttribute()},
		{GetAttributeTagMaxMana(), UAuraAttributeSet::GetMaxManaAttribute()},
		{GetAttributeTagFireResistance(), UAuraAttributeSet::GetFireResistanceAttribute()},
		{GetAttributeTagLightningResistance(), UAuraAttributeSet::GetLightningResistanceAttribute()},
		{GetAttributeTagArcaneResistance(), UAuraAttributeSet::GetArcaneResistanceAttribute()},
		{GetAttributeTagPhysicalResistance(), UAuraAttributeSet::GetPhysicalResistanceAttribute()}
	};

	return AttributeMap;
}

// 伤害类型和对应的护甲类型
const TMap<FGameplayTag, FGameplayTag>& FAuraGameplayTags::GetDamageTypeMap()
{
	static TMap<FGameplayTag, FGameplayTag> DamageTypeMap{
		{GetDamageTypeTagFire(), GetAttributeTagFireResistance()},
		{GetDamageTypeTagLightning(), GetAttributeTagLightningResistance()},
		{GetDamageTypeTagArcane(), GetAttributeTagArcaneResistance()},
		{GetDamageTypeTagPhysical(), GetAttributeTagPhysicalResistance()},
	};

	return DamageTypeMap;
}

// Input Tag

#define IMPLEMENT_INPUT_TAG(ClassName, InputName) IMPLEMENT_TAG(ClassName, INPUT_TAG_NAME(InputName))

IMPLEMENT_INPUT_TAG(FAuraGameplayTags, LMB);
IMPLEMENT_INPUT_TAG(FAuraGameplayTags, RMB);
IMPLEMENT_INPUT_TAG(FAuraGameplayTags, 1);
IMPLEMENT_INPUT_TAG(FAuraGameplayTags, 2);
IMPLEMENT_INPUT_TAG(FAuraGameplayTags, 3);
IMPLEMENT_INPUT_TAG(FAuraGameplayTags, 4);
IMPLEMENT_INPUT_TAG(FAuraGameplayTags, Move);
IMPLEMENT_INPUT_TAG(FAuraGameplayTags, Shift);

#define INPUT_TAG_STR(InputName) "Input." #InputName

#define ADD_NATIVE_INPUT_TAG(InputName, TagDevComment) \
	INPUT_TAG_NAME(InputName) = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(INPUT_TAG_STR(InputName)), TagDevComment);

// Effect Tag

#define IMPLEMENT_EFFECT_TAG(ClassName, EffectName) IMPLEMENT_TAG(ClassName, EFFECT_TAG_NAME(EffectName))
#define EFFECT_TAG_STR(EffectName) "Effect." #EffectName
#define ADD_NATIVE_EFFECT_TAG(EffectName, TagDevComment) \
	EFFECT_TAG_NAME(EffectName) = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(EFFECT_TAG_STR(EffectName)), TagDevComment);

IMPLEMENT_EFFECT_TAG(FAuraGameplayTags, Damage);
IMPLEMENT_EFFECT_TAG(FAuraGameplayTags, HitReact);

// Damage Type Tag

#define IMPLEMENT_DAMAGE_TYPE_TAG(ClassName, DamageTypeName) IMPLEMENT_TAG(ClassName, DAMAGE_TYPE_TAG_NAME(DamageTypeName))
#define DAMAGE_TYPE_TAG_STR(DamageTypeName) "DamageType." #DamageTypeName
#define ADD_NATIVE_DAMAGE_TYPE_TAG(DamageTypeName, TagDevComment) \
	DAMAGE_TYPE_TAG_NAME(DamageTypeName) = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(DAMAGE_TYPE_TAG_STR(DamageTypeName)), TagDevComment);

IMPLEMENT_DAMAGE_TYPE_TAG(FAuraGameplayTags, Fire);
IMPLEMENT_DAMAGE_TYPE_TAG(FAuraGameplayTags, Lightning);
IMPLEMENT_DAMAGE_TYPE_TAG(FAuraGameplayTags, Arcane);
IMPLEMENT_DAMAGE_TYPE_TAG(FAuraGameplayTags, Physical);

// Initialize

void FAuraGameplayTags::InitializeAuraGameplayTags()
{
	REQUEST_VITAL_ATTRIBUTE_TAG(Health);
	REQUEST_VITAL_ATTRIBUTE_TAG(Mana);

	REQUEST_PRIMARY_ATTRIBUTE_TAG(Strength);
	REQUEST_PRIMARY_ATTRIBUTE_TAG(Intelligence);
	REQUEST_PRIMARY_ATTRIBUTE_TAG(Resilience);
	REQUEST_PRIMARY_ATTRIBUTE_TAG(Vigor);

	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(Armor, "Reduces damage taken, improves block chance");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(ArmorPenetration, "Ignore percentage of enemy Armor, increases crictical hit damage");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(BlockChance, "Chance to cut incoming damage in half");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(CriticalHitChance, "Chance to double damage plus crictical hit bonus");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(CriticalHitDamage, "Bonus damage added when a crictical hit is scored");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(CriticalHitResistance, "Reduces crictical hit chance of attacking enemies");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(HealthRegeneration, "Amount of health regenerated every second");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(ManaRegeneration, "Amount of mana regenerated every second");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(MaxHealth, "Maxium amount of health obtainable");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(MaxMana, "Maxium amount of mana obtainable");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(FireResistance, "Resistance to Fire Damage");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(LightningResistance, "Resistance to Lightning Damage");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(ArcaneResistance, "Resistance to Arcane Damage");
	ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(PhysicalResistance, "Resistance to Physical Damage");

	ADD_NATIVE_INPUT_TAG(LMB, "Input Tag for Left Mouse Button");
	ADD_NATIVE_INPUT_TAG(RMB, "Input Tag for Right Mouse Button");
	ADD_NATIVE_INPUT_TAG(1, "Input Tag for 1 Key");
	ADD_NATIVE_INPUT_TAG(2, "Input Tag for 2 Key");
	ADD_NATIVE_INPUT_TAG(3, "Input Tag for 3 Key");
	ADD_NATIVE_INPUT_TAG(4, "Input Tag for 4 Key");
	ADD_NATIVE_INPUT_TAG(Move, "Input Tag for Move");
	ADD_NATIVE_INPUT_TAG(Shift, "Input Tag for Shift Key");

	ADD_NATIVE_EFFECT_TAG(Damage, "");
	ADD_NATIVE_EFFECT_TAG(HitReact, "Tag granted when reacting to hit");

	ADD_NATIVE_DAMAGE_TYPE_TAG(Fire, "Fire Damage Tag");
	ADD_NATIVE_DAMAGE_TYPE_TAG(Lightning, "Lightning Damage Tag");
	ADD_NATIVE_DAMAGE_TYPE_TAG(Arcane, "Arcane Damage Tag");
	ADD_NATIVE_DAMAGE_TYPE_TAG(Physical, "Physical Damage Tag");
}
