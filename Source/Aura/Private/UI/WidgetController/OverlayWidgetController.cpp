// Copyright Yang Dong


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const auto& Attributes = AbilitySystemComponent->GetSet<UAuraAttributeSet>();

	OnHealthChanged.Broadcast(Attributes->GetHealth(), true);
	OnMaxHealthChanged.Broadcast(Attributes->GetMaxHealth(), true);
	OnManaChanged.Broadcast(Attributes->GetMana(), true);
	OnMaxManaChanged.Broadcast(Attributes->GetMaxMana(), true);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const auto& Attributes = AbilitySystemComponent->GetSet<UAuraAttributeSet>();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this, &ThisClass::HandleHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HandleMaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetManaAttribute()).AddUObject(this, &ThisClass::HandleManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxManaAttribute()).AddUObject(this, &ThisClass::HandleMaxManaChanged);
	AbilitySystemComponent->GetOnEffectAssetTags().AddUObject(this, &ThisClass::HandleMessageTags);
}

void UOverlayWidgetController::HandleHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue, false);
}

void UOverlayWidgetController::HandleMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue, false);
}

void UOverlayWidgetController::HandleManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue, false);
}

void UOverlayWidgetController::HandleMaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue, false);
}

void UOverlayWidgetController::HandleMessageTags_Implementation(FGameplayTagContainer MessageTags)
{
	for (const FGameplayTag& Tag : MessageTags)
	{
		if (FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message")); !Tag.MatchesTag(MessageTag)) continue;

		if (const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag))
		{
			OnUIMessage.Broadcast(*Row);
		}
	}
}
