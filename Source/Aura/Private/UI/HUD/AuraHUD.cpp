// Copyright Yang Dong


#include "UI/HUD/AuraHUD.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Player/AuraPlayerState.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

void AAuraHUD::Initialize(UAbilitySystemComponent* AbilitySystemComponent)
{
	for (const auto& Pair : WidgetClasses)
	{
		const auto& EWidget = Pair.Key;
		const auto& WidgetClass = Pair.Value;

		const auto& WidgetObject = Widgets.Add(EWidget, CreateWidget<UAuraUserWidget>(GetWorld(), WidgetClass));
		WidgetObject->SetWidgetController(GetWidgetController(EWidget, AbilitySystemComponent));
		WidgetObject->AddToViewport();
	}
}

bool AAuraHUD::AddWidgetToViewPort(EHUDWidget Widget)
{
	if (Widgets.Find(Widget))
	{
		Widgets[Widget]->AddToViewport();
		return true;
	}

	return false;
}

UAuraWidgetController* AAuraHUD::GetWidgetController(const EHUDWidget Widget, UAbilitySystemComponent* AbilitySystemComponent)
{
	if (!WidgetControllers.Find(Widget))
	{
		const auto& Class = *WidgetControllerClasses.Find(Widget);
		check(Class);

		const auto& WidgetController = WidgetControllers.Add(Widget, NewObject<UAuraWidgetController>(this, Class));
		WidgetController->Initialize(AbilitySystemComponent);
	}

	return WidgetControllers[Widget];
}
