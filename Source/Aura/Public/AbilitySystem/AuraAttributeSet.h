// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Marco.h"
#include "AuraAttributeSet.generated.h"

// Setter 通过 ASC 设置 BaseValue ，Initter 直接设置 BaseValue 和 CurrentValue
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)           \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName) Attribute_##AttributeClass##_##AttributeName
#define DECLARE_ATTRIBUTE_TAG(AttributeClass, AttributeName) static FGameplayTag ATTRIBUTE_TAG_NAME(AttributeClass, AttributeName);
#define DECLARE_VITAL_ATTRIBUTE_TAG(AttributeName) DECLARE_ATTRIBUTE_TAG(Vital, AttributeName)
#define DECLARE_PRIMARY_ATTRIBUTE_TAG(AttributeName) DECLARE_ATTRIBUTE_TAG(Primary, AttributeName)
#define DECLARE_SECONDARY_ATTRIBUTE_TAG(AttributeName) DECLARE_ATTRIBUTE_TAG(Secondary, AttributeName)

#define ATTRIBUTE_TAG_GETTER(AttributeClass, AttributeName)      \
	static const FGameplayTag& GetAttributeTag##AttributeName()  \
	{                                                            \
		return Attribute_##AttributeClass##_##AttributeName;     \
	}

#define VITAL_ATTRIBUTE_TAG_GETTER(AttributeName)  ATTRIBUTE_TAG_GETTER(Vital, AttributeName)
#define PRIMARY_ATTRIBUTE_TAG_GETTER(AttributeName) ATTRIBUTE_TAG_GETTER(Primary, AttributeName)
#define SECONDARY_ATTRIBUTE_TAG_GETTER(AttributeName) ATTRIBUTE_TAG_GETTER(Secondary, AttributeName)

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	static void InitializeAttributeTag();

	// Vital Attributes

	ATTRIBUTE_ACCESSORS(ThisClass, Health);
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);

	VITAL_ATTRIBUTE_TAG_GETTER(Health);
	VITAL_ATTRIBUTE_TAG_GETTER(Mana);

	// Primary Attributes

	ATTRIBUTE_ACCESSORS(ThisClass, Strength);
	ATTRIBUTE_ACCESSORS(ThisClass, Intelligence);
	ATTRIBUTE_ACCESSORS(ThisClass, Resilience);
	ATTRIBUTE_ACCESSORS(ThisClass, Vigor);

	PRIMARY_ATTRIBUTE_TAG_GETTER(Strength);
	PRIMARY_ATTRIBUTE_TAG_GETTER(Intelligence);
	PRIMARY_ATTRIBUTE_TAG_GETTER(Resilience);
	PRIMARY_ATTRIBUTE_TAG_GETTER(Vigor);

	// Secondary Attributes

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

	static const TArray<FGameplayAttribute>& GetPrimaryAttributes();
	static const TArray<FGameplayAttribute>& GetSecondaryAttributes();
	static const TArray<FGameplayAttribute>& GetVitalAttributes();
	static const TArray<FGameplayAttribute>& GetAttributes();
	
	STATIC_CONST_REF_GETTER(PrimaryAttributeTags);
	STATIC_CONST_REF_GETTER(SecondaryAttributeTags);
	STATIC_CONST_REF_GETTER(VitalAttributeTags);
	STATIC_CONST_REF_GETTER(AttributeMap);
protected:
	static TArray<FGameplayTag> VitalAttributeTags;
	static TArray<FGameplayTag> PrimaryAttributeTags;
	static TArray<FGameplayTag> SecondaryAttributeTags;
	static TMap<FGameplayTag, FGameplayAttribute> AttributeMap;
	
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
	DECLARE_VITAL_ATTRIBUTE_TAG(Health);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Vital Attributes", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	DECLARE_VITAL_ATTRIBUTE_TAG(Mana);

	// Primary Attributes

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Primary Attributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	DECLARE_PRIMARY_ATTRIBUTE_TAG(Strength);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Primary Attributes", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	DECLARE_PRIMARY_ATTRIBUTE_TAG(Intelligence);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Primary Attributes", ReplicatedUsing = OnRep_Resilience)
	FGameplayAttributeData Resilience;
	DECLARE_PRIMARY_ATTRIBUTE_TAG(Resilience);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Primary Attributes", ReplicatedUsing = OnRep_Vigor)
	FGameplayAttributeData Vigor;
	DECLARE_PRIMARY_ATTRIBUTE_TAG(Vigor);

	// Secondary Attributes

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(Armor);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(BlockChance);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(MaxHealth);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Aura|Secondary Attributes", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	DECLARE_SECONDARY_ATTRIBUTE_TAG(MaxMana);
};
