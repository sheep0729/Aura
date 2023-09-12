// Copyright Yang Dong


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::Initialize(UAbilitySystemComponent* AbilitySystemComponent)
{
	WidgetControllerActorInfo.InitFromAbilitySystemComponent(AbilitySystemComponent);
	BindCallbacksToDependencies();
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}
