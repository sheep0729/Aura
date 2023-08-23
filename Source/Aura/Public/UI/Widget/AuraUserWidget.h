// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

class UAuraWidgetController;

UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UAuraWidgetController* InWidgetController)
	{
		WidgetController = InWidgetController;
		OnWidgetControllerSet();
	}

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UAuraWidgetController> WidgetController;
};
