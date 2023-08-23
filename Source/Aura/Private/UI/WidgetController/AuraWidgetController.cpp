// Copyright Yang Dong


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::InitWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	Attributes = WidgetControllerParams.Attributes;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}
