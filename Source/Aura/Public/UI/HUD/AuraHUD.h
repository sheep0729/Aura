// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;

UENUM()
enum class FAuraWidget
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
    template <typename T>
    T* GetWidgetController(FAuraWidget AuraWidget);

    void Init(AAuraPlayerController* PlayerController, AAuraPlayerState* PlayerState, UAuraAbilitySystemComponent* AbilitySystemComponent);

private:
    UAuraWidgetController* GetWidgetController(FAuraWidget AuraWidget);

    UPROPERTY()
    TMap<FAuraWidget, UAuraUserWidget*> Widgets;

    UPROPERTY(EditAnywhere, Category = "Custom")
    TMap<FAuraWidget, TSubclassOf<UAuraUserWidget>> WidgetClasses;

    UPROPERTY()
    TMap<FAuraWidget, UAuraWidgetController*> WidgetControllers;

    UPROPERTY(EditAnywhere, Category = "Custom")
    TMap<FAuraWidget, TSubclassOf<UAuraWidgetController>> WidgetControllerClasses;

    UPROPERTY()
    FWidgetControllerParams WidgetControllerParams;
};

template <typename T>
T* AAuraHUD::GetWidgetController(const FAuraWidget AuraWidget)
{
    return Cast<T>(GetWidgetController(AuraWidget));
}
