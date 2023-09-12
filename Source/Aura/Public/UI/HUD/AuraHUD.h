// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
struct FWidgetControllerActorInfo;
class UOverlayWidgetController;
class UAuraUserWidget;

UENUM()
enum class EHUDWidget
{
	None,
	Overlay,
	AttributeMenu,
};

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	// template <typename T>
	// T* GetWidgetController();
	
	void Initialize(UAbilitySystemComponent* AbilitySystemComponent);

	bool AddWidgetToViewPort(EHUDWidget Widget);

private:
	UAuraWidgetController* GetWidgetController(const EHUDWidget Widget, UAbilitySystemComponent* AbilitySystemComponent);

	UPROPERTY()
	TMap<EHUDWidget, UAuraUserWidget*> Widgets;

	UPROPERTY(EditDefaultsOnly)
	TMap<EHUDWidget, TSubclassOf<UAuraUserWidget>> WidgetClasses;
	
	UPROPERTY()
	TMap<EHUDWidget, UAuraWidgetController*> WidgetControllers;

	UPROPERTY(EditDefaultsOnly)
	TMap<EHUDWidget, TSubclassOf<UAuraWidgetController>> WidgetControllerClasses;
};

// template <typename T>
// T* AAuraHUD::GetWidgetController()
// {
//     return Cast<T>(GetWidgetController(T::StaticClass()));
// }
