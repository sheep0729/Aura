// Copyright Yang Dong

#include "GameplayTagsManager.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Vigor, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
}

#define ON_REP_ATTRIBUTE(ClassName, PropertyName)                                                 \
	void ClassName::OnRep_##PropertyName(const FGameplayAttributeData& Old##PropertyName) const { \
		GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, Old##PropertyName)                   \
	}

ON_REP_ATTRIBUTE(UAuraAttributeSet, Health);
ON_REP_ATTRIBUTE(UAuraAttributeSet, Mana);

ON_REP_ATTRIBUTE(UAuraAttributeSet, Strength);
ON_REP_ATTRIBUTE(UAuraAttributeSet, Intelligence);
ON_REP_ATTRIBUTE(UAuraAttributeSet, Resilience);
ON_REP_ATTRIBUTE(UAuraAttributeSet, Vigor);

ON_REP_ATTRIBUTE(UAuraAttributeSet, Armor);
ON_REP_ATTRIBUTE(UAuraAttributeSet, ArmorPenetration);
ON_REP_ATTRIBUTE(UAuraAttributeSet, BlockChance);
ON_REP_ATTRIBUTE(UAuraAttributeSet, CriticalHitChance);
ON_REP_ATTRIBUTE(UAuraAttributeSet, CriticalHitDamage);
ON_REP_ATTRIBUTE(UAuraAttributeSet, CriticalHitResistance);
ON_REP_ATTRIBUTE(UAuraAttributeSet, HealthRegeneration);
ON_REP_ATTRIBUTE(UAuraAttributeSet, ManaRegeneration);
ON_REP_ATTRIBUTE(UAuraAttributeSet, MaxHealth);
ON_REP_ATTRIBUTE(UAuraAttributeSet, MaxMana);

const TArray<FGameplayAttribute>& UAuraAttributeSet::GetPrimaryAttributes()
{
	static TArray PrimaryAttributes{
		GetStrengthAttribute(),
		GetIntelligenceAttribute(),
		GetResilienceAttribute(),
		GetVigorAttribute()
	};

	return PrimaryAttributes;
}

const TArray<FGameplayAttribute>& UAuraAttributeSet::GetSecondaryAttributes()
{
	static TArray SecondaryAttributes{
		GetArmorAttribute(),
		GetArmorPenetrationAttribute(),
		GetBlockChanceAttribute(),
		GetCriticalHitChanceAttribute(),
		GetCriticalHitDamageAttribute(),
		GetCriticalHitResistanceAttribute(),
		GetHealthRegenerationAttribute(),
		GetManaRegenerationAttribute(),
		GetMaxHealthAttribute(),
		GetMaxManaAttribute()
	};

	return SecondaryAttributes;
}

const TArray<FGameplayAttribute>& UAuraAttributeSet::GetVitalAttributes()
{
	static TArray VitalAttributes{
		GetHealthAttribute(),
		GetManaAttribute()
	};

	return VitalAttributes;
}

const TArray<FGameplayAttribute>& UAuraAttributeSet::GetAttributes()
{
	static TArray Attributes{
		GetHealthAttribute(),
		GetManaAttribute(),
		GetStrengthAttribute(),
		GetIntelligenceAttribute(),
		GetResilienceAttribute(),
		GetVigorAttribute(),
		GetArmorAttribute(),
		GetArmorPenetrationAttribute(),
		GetBlockChanceAttribute(),
		GetCriticalHitChanceAttribute(),
		GetCriticalHitDamageAttribute(),
		GetCriticalHitResistanceAttribute(),
		GetHealthRegenerationAttribute(),
		GetManaRegenerationAttribute(),
		GetMaxHealthAttribute(),
		GetMaxManaAttribute()
	};

	return Attributes;
}

// Tag 关联 Attribute
// TODO 如果没有什么实际用途的话应该考虑删掉

TArray<FGameplayTag> UAuraAttributeSet::VitalAttributeTags;
TArray<FGameplayTag> UAuraAttributeSet::PrimaryAttributeTags;
TArray<FGameplayTag> UAuraAttributeSet::SecondaryAttributeTags;
TMap<FGameplayTag, FGameplayAttribute> UAuraAttributeSet::AttributeMap;

#define IMPLEMENT_ATTRIBUTE_TAG(ClassName, AttributeClass, AttributeName) FGameplayTag ClassName::Attribute_##AttributeClass##_##AttributeName;
#define IMPLEMENT_VITAL_ATTRIBUTE_TAG(ClassName, AttributeName) IMPLEMENT_ATTRIBUTE_TAG(ClassName, Vital, AttributeName)
#define IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(ClassName, AttributeName) IMPLEMENT_ATTRIBUTE_TAG(ClassName, Primary, AttributeName)
#define IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(ClassName, AttributeName) IMPLEMENT_ATTRIBUTE_TAG(ClassName, Secondary, AttributeName)

IMPLEMENT_VITAL_ATTRIBUTE_TAG(UAuraAttributeSet, Health);
IMPLEMENT_VITAL_ATTRIBUTE_TAG(UAuraAttributeSet, Mana);

IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(UAuraAttributeSet, Strength);
IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(UAuraAttributeSet, Intelligence);
IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(UAuraAttributeSet, Resilience);
IMPLEMENT_PRIMARY_ATTRIBUTE_TAG(UAuraAttributeSet, Vigor);

IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, Armor);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, ArmorPenetration);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, BlockChance);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, CriticalHitChance);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, CriticalHitDamage);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, CriticalHitResistance);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, HealthRegeneration);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, ManaRegeneration);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, MaxHealth);
IMPLEMENT_SECONDARY_ATTRIBUTE_TAG(UAuraAttributeSet, MaxMana);

#define ATTRIBUTE_TAG_STR(AttributeClass, AttributeName) "Attributes." #AttributeClass "." #AttributeName

#define REQUEST_ATTRIBUTE_TAG(AttributeClass, AttributeName) \
	ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName) = FGameplayTag::RequestGameplayTag(FName(ATTRIBUTE_TAG_STR(AttributeClass, AttributeName)))
#define REQUEST_VITAL_ATTRIBUTE_TAG(AttributeName) REQUEST_ATTRIBUTE_TAG(Vital, AttributeName)
#define REQUEST_PRIMARY_ATTRIBUTE_TAG(AttributeName) REQUEST_ATTRIBUTE_TAG(Primary, AttributeName)

#define ADD_NATIVE_ATTRIBUTE_TAG(AttributeClass, AttributeName, TagDevComment) \
   ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName) = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(ATTRIBUTE_TAG_STR(AttributeClass, AttributeName)), TagDevComment);
#define ADD_NATIVE_SECONDARY_ATTRIBUTE_TAG(AttributeName, TagDevComment) ADD_NATIVE_ATTRIBUTE_TAG(Secondary, AttributeName, TagDevComment)

void UAuraAttributeSet::InitializeAttributeTag()
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

	VitalAttributeTags = {
		GetAttributeTagHealth(),
		GetAttributeTagMana()
	};

	PrimaryAttributeTags = {
		GetAttributeTagStrength(),
		GetAttributeTagIntelligence(),
		GetAttributeTagResilience(),
		GetAttributeTagVigor()
	};

	SecondaryAttributeTags = {
		GetAttributeTagArmor(),
		GetAttributeTagArmorPenetration(),
		GetAttributeTagBlockChance(),
		GetAttributeTagCriticalHitChance(),
		GetAttributeTagCriticalHitDamage(),
		GetAttributeTagCriticalHitResistance(),
		GetAttributeTagHealthRegeneration(),
		GetAttributeTagManaRegeneration(),
		GetAttributeTagMaxHealth(),
		GetAttributeTagMaxMana()
	};

	AttributeMap = {
		{GetAttributeTagHealth(), GetHealthAttribute()},
		{GetAttributeTagMana(), GetManaAttribute()},

		{GetAttributeTagStrength(), GetStrengthAttribute()},
		{GetAttributeTagIntelligence(), GetIntelligenceAttribute()},
		{GetAttributeTagResilience(), GetResilienceAttribute()},
		{GetAttributeTagVigor(), GetVigorAttribute()},

		{GetAttributeTagArmor(), GetArmorAttribute()},
		{GetAttributeTagArmorPenetration(), GetArmorPenetrationAttribute()},
		{GetAttributeTagBlockChance(), GetBlockChanceAttribute()},
		{GetAttributeTagCriticalHitChance(), GetCriticalHitChanceAttribute()},
		{GetAttributeTagCriticalHitDamage(), GetCriticalHitDamageAttribute()},
		{GetAttributeTagCriticalHitResistance(), GetCriticalHitResistanceAttribute()},
		{GetAttributeTagHealthRegeneration(), GetHealthRegenerationAttribute()},
		{GetAttributeTagManaRegeneration(), GetManaRegenerationAttribute()},
		{GetAttributeTagMaxHealth(), GetMaxHealthAttribute()},
		{GetAttributeTagMaxMana(), GetMaxManaAttribute()}
	};
}
