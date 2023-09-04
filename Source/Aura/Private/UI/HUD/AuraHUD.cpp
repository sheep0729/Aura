// Copyright Yang Dong


#include "UI/HUD/AuraHUD.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Player/AuraPlayerState.h"
#include "UI/Widget/AuraUserWidget.h" // 这行是需要的，Rider 有问题
#include "UI/WidgetController/AttributeMenuWidgetController.h"

void AAuraHUD::Init(AAuraPlayerController* PlayerController, AAuraPlayerState* PlayerState, UAuraAbilitySystemComponent* AbilitySystemComponent)
{
	WidgetControllerParams = {PlayerController, PlayerState, AbilitySystemComponent};
	
	for (const auto& Pair : WidgetClasses)
	{
		const auto& AuraWidget = Pair.Key;
		const auto& WidgetClass = Pair.Value;
		Widgets.Add(AuraWidget, CreateWidget<UAuraUserWidget>(GetWorld(), WidgetClass));
	}

	if (Widgets.Find(FAuraWidget::Overlay))
	{
		Widgets[FAuraWidget::Overlay]->AddToViewport();
	}
}

UAuraWidgetController* AAuraHUD::GetWidgetController(const FAuraWidget AuraWidget)
{
	if (!WidgetControllers.Find(AuraWidget))
	{
		const auto& Class = *WidgetControllerClasses.Find(AuraWidget);
		check(Class);
		
		const auto& WidgetController = WidgetControllers.Add(AuraWidget, NewObject<UAuraWidgetController>(this, Class));
		WidgetController->InitWidgetController(WidgetControllerParams);
		WidgetController->BindCallbacksToDependencies();
	}

	return WidgetControllers[AuraWidget];
}
