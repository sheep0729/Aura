// Copyright Yang Dong


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AttributeInfo.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	for (const auto& Attribute : UAuraAttributeSet::GetAttributes())
	{
		WidgetControllerActorInfo.GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &ThisClass::HandleAttributeValueChanged);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	for (const auto& Attribute : UAuraAttributeSet::GetAttributes())
	{
		OnAttributeInfo.Broadcast(GetAttributeInfo(Attribute));
	}
}

void UAttributeMenuWidgetController::HandleAttributeValueChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeInfo.Broadcast(GetAttributeInfo(Data.Attribute));
}

const FAuraAttributeInfo& UAttributeMenuWidgetController::GetAttributeInfo(const FGameplayAttribute& Attribute)
{
	const auto& Info = AttributeInfoData->GetAttributeInfo(Attribute);
	Info.AttributeValue = WidgetControllerActorInfo.GetAbilitySystemComponent()->GetNumericAttribute(Attribute);
	return Info;
}
