// Copyright Yang Dong


#include "UI/HUD/AuraHUD.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Player/AuraPlayerState.h"
#include "UI/Widget/AuraUserWidget.h" // 这行是需要的，Rider 有问题
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController()
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->InitWidgetController(OverlayWidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(AAuraPlayerController* PC, AAuraPlayerState* PS, UAuraAbilitySystemComponent* ASC, UAuraAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass == nullptr"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass == nullptr"));
	
	UAuraUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidgetControllerParams = FWidgetControllerParams{PC, PS, ASC, AS};
	
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController();
	Widget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}