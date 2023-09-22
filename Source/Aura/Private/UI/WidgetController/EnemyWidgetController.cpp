// Copyright Yang Dong


#include "UI/WidgetController/EnemyWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UEnemyWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const auto& Attributes = WidgetControllerActorInfo.GetAbilitySystemComponent()->GetSet<UAuraAttributeSet>();

	OnHealthChanged.Broadcast(Attributes->GetHealth(), true);
	OnMaxHealthChanged.Broadcast(Attributes->GetMaxHealth(), true);
}

void UEnemyWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const auto& AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(WidgetControllerActorInfo.GetAbilitySystemComponent());
	const auto& Attributes = AbilitySystemComponent->GetSet<UAuraAttributeSet>();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this, &ThisClass::HandleHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HandleMaxHealthChanged);
}

void UEnemyWidgetController::HandleHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue, false);
}

void UEnemyWidgetController::HandleMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue, false);
}
