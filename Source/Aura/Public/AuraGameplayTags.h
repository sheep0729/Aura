// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"

#define DECLARE_TAG(TagName) static FGameplayTag TagName;

#define ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName) Attribute_##AttributeClass##_##AttributeName

#define DECLARE_ATTRIBUTE_TAG(AttributeClass, AttributeName) DECLARE_TAG(ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName));
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

#define INPUT_TAG_NAME(InputName) InputTag_##InputName
#define DECLARE_INPUT_TAG(InputName) DECLARE_TAG(INPUT_TAG_NAME(InputName));

#define INPUT_TAG_GETTER(InputName)                     \
	static const FGameplayTag& GetInputTag##InputName() \
	{                                                   \
		return INPUT_TAG_NAME(InputName);               \
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

	DECLARE_INPUT_TAG(LMB);
	DECLARE_INPUT_TAG(RMB);
	DECLARE_INPUT_TAG(1);
	DECLARE_INPUT_TAG(2);
	DECLARE_INPUT_TAG(3);
	DECLARE_INPUT_TAG(4);
};
