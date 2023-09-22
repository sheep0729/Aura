// Copyright Yang Dong

#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AuraGameplayEffectTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>

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
		 //UE_LOG(LogTemp, Log, TEXT("New Health = %f"), NewValue);
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		SetHealth(FMath::Min(GetHealth(), GetMaxHealth()));
		// UE_LOG(LogTemp, Log, TEXT("New Max Health = %f"), NewValue);
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxMana());
		// UE_LOG(LogTemp, Log, TEXT("New Mana = %f"), NewValue);
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		SetMana(FMath::Min(GetMana(), GetMaxMana()));
		// UE_LOG(LogTemp, Log, TEXT("New Max Mana = %f"), NewValue);
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Source = causer if the effect, Target = target of the effect (owner of this AS)

	FEffectContextData EffectContextData = FEffectContextData::GetEffectContextData(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
		UKismetSystemLibrary::PrintString(Data.Target.GetAvatarActor(),
		                                  FString::Format(
			                                  TEXT("Changed Health on [{0}], Health = [{1}]"), {Data.Target.GetAvatarActor()->GetName(), GetHealth()}),
		                                  true, true, FLinearColor::Green, 2, FName(GetNameSafe(this)));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		//SetMana(FMath::Clamp(GetMana(), 0, GetMaxMana()));
	}
	else if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float Damage = GetIncomingDamage();
		const float OldHealth = GetHealth();
		const float NewHealth = FMath::Max(0, OldHealth - Damage);
		SetHealth(NewHealth);
		SetIncomingDamage(0);

		const auto TargetASC = Cast<UAuraAbilitySystemComponent>(EffectContextData.Target.AbilitySystemComponent);
		TargetASC->GetOnDamaged().Broadcast(Damage, OldHealth, NewHealth);
	}
}
