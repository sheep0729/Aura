// Copyright Yang Dong


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Data/AuraGameplayTags.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "Marco.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"

const TArray<FGameplayTag>& UAuraAbilitySystemLibrary::GetPrimaryAttributeTags()
{
	return FAuraGameplayTags::GetPrimaryAttributeTags();
}

const TArray<FGameplayTag>& UAuraAbilitySystemLibrary::GetSecondaryAttributeTags()
{
	return FAuraGameplayTags::GetSecondaryAttributeTags();
}

const FGameplayAttribute& UAuraAbilitySystemLibrary::GetAttributesByTag(const FGameplayTag& AttributeTag)
{
	const auto AttributePtr = FAuraGameplayTags::GetAttributeMap().Find(AttributeTag);
	check(AttributePtr);
	return *AttributePtr;
}

FString UAuraAbilitySystemLibrary::GetAttributeName(const FGameplayAttribute& Attribute)
{
	return Attribute.AttributeName;
}

const TArray<FGameplayAttribute>& UAuraAbilitySystemLibrary::GetAttributes()
{
	return UAuraAttributeSet::GetAttributes();
}

const TArray<FGameplayAttribute>& UAuraAbilitySystemLibrary::GetPrimaryAttributes()
{
	return UAuraAttributeSet::GetPrimaryAttributes();
}

const TArray<FGameplayAttribute>& UAuraAbilitySystemLibrary::GetSecondaryAttributes()
{
	return UAuraAttributeSet::GetSecondaryAttributes();
}
