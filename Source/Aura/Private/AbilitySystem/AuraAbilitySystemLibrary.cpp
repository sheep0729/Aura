// Copyright Yang Dong


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "Marco.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UAuraUserWidget* AuraUserWidget)
{
	NULL_RETURN_VALUE(AuraUserWidget, nullptr);

	const auto PlayerController = AuraUserWidget->GetOwningPlayer();
	NULL_RETURN_VALUE(PlayerController, nullptr);

	AAuraHUD* HUD = Cast<AAuraHUD>(PlayerController->GetHUD());
	NULL_RETURN_VALUE(HUD, nullptr);

	return HUD->GetWidgetController<UOverlayWidgetController>(FAuraWidget::Overlay);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UAuraUserWidget* AuraUserWidget)
{
	NULL_RETURN_VALUE(AuraUserWidget, nullptr);

	const auto PlayerController = AuraUserWidget->GetOwningPlayer();
	NULL_RETURN_VALUE(PlayerController, nullptr);

	AAuraHUD* HUD = Cast<AAuraHUD>(PlayerController->GetHUD());
	NULL_RETURN_VALUE(HUD, nullptr);

	return HUD->GetWidgetController<UAttributeMenuWidgetController>(FAuraWidget::AttributeMenu);
}

const TArray<FGameplayTag>& UAuraAbilitySystemLibrary::GetPrimaryAttributeTags()
{
	return UAuraAttributeSet::GetPrimaryAttributeTags();
}

const TArray<FGameplayTag>& UAuraAbilitySystemLibrary::GetSecondaryAttributeTags()
{
	return UAuraAttributeSet::GetSecondaryAttributeTags();
}

const FGameplayAttribute& UAuraAbilitySystemLibrary::GetAttributesByTag(const FGameplayTag& AttributeTag)
{
	const auto AttributePtr = UAuraAttributeSet::GetAttributeMap().Find(AttributeTag);
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
