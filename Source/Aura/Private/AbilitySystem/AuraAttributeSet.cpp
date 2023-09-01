// Copyright Yang Dong

#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AuraGameplayEffectTypes.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	// InitHealth(50);
	// InitMaxHealth(100);
	// InitMana(50);
	// InitMaxMana(100);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
		// UE_LOG(LogTemp, Log, TEXT("New Health = %f"), NewValue);
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		// UE_LOG(LogTemp, Log, TEXT("New Max Health = %f"), NewValue);
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxMana());
		// UE_LOG(LogTemp, Log, TEXT("New Mana = %f"), NewValue);
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		// UE_LOG(LogTemp, Log, TEXT("New Max Mana = %f"), NewValue);
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Source = causer if the effect, Target = target of the effect (owner of this AS)

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0, GetMaxMana()));
	}

	FEffectContextData EffectContextData = FEffectContextData::GetEffectContextData(Data);
}

