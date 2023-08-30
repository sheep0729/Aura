﻿// Copyright Yang Dong

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

#define ON_REP_ATTRIBUTE(ClassName, PropertyName)                                \
void ClassName::OnRep_##PropertyName(const FGameplayAttributeData& Old##PropertyName) const { \
GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, Old##PropertyName) \
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