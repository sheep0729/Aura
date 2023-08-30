// Copyright Yang Dong


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	OnHealthChanged.Broadcast(Attributes->GetHealth());
	OnMaxHealthChanged.Broadcast(Attributes->GetMaxHealth());
	OnManaChanged.Broadcast(Attributes->GetMana());
	OnMaxManaChanged.Broadcast(Attributes->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this, &ThisClass::HandleHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HandleMaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetManaAttribute()).AddUObject(this, &ThisClass::HandleManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxManaAttribute()).AddUObject(this, &ThisClass::HandleMaxManaChanged);
	AbilitySystemComponent->GetOnEffectAssetTags().AddUObject(this, &ThisClass::HandleMessageTags);
}

void UOverlayWidgetController::HandleHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HandleMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HandleManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HandleMaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HandleMessageTags(const FGameplayTagContainer& MessageTags) const
{
	for (const FGameplayTag& Tag : MessageTags)
	{
		if (FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message")); !Tag.MatchesTag(MessageTag)) continue;
		// GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Cyan, FString::Format(TEXT("GE Asset Tag: {0}"), {Tag.ToString()}));
		const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
		OnUIMessage.Broadcast(*Row);
	}
}
