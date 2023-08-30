// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AuraAttributeSet.generated.h"

// Setter 通过 ASC 设置 BaseValue ，Initter 直接设置 BaseValue 和 CurrentValue
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)           \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	ATTRIBUTE_ACCESSORS(ThisClass, Health);
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);

	ATTRIBUTE_ACCESSORS(ThisClass, Strength);
	ATTRIBUTE_ACCESSORS(ThisClass, Intelligence);
	ATTRIBUTE_ACCESSORS(ThisClass, Resilience);
	ATTRIBUTE_ACCESSORS(ThisClass, Vigor);

	ATTRIBUTE_ACCESSORS(ThisClass, Armor);
	ATTRIBUTE_ACCESSORS(ThisClass, ArmorPenetration);
	ATTRIBUTE_ACCESSORS(ThisClass, BlockChance);
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitChance);
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitDamage);
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitResistance);
	ATTRIBUTE_ACCESSORS(ThisClass, HealthRegeneration);
	ATTRIBUTE_ACCESSORS(ThisClass, ManaRegeneration);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

private:
	// Vital Attributes

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Vital Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Vital Attributes", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;

	// Primary Attributes

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Primary Attributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Primary Attributes", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Primary Attributes", ReplicatedUsing = OnRep_Resilience)
	FGameplayAttributeData Resilience;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Primary Attributes", ReplicatedUsing = OnRep_Vigor)
	FGameplayAttributeData Vigor;

	// Secondary Attributes

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_BlockChance)
	FGameplayAttributeData BlockChance;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
};
