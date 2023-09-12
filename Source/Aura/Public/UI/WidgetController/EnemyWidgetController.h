// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "EnemyWidgetController.generated.h"
 
UCLASS()
class AURA_API UEnemyWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "Custom|GAS|Attributes")
	FOnAttributeChangedSingature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Custom|GAS|Attributes")
	FOnAttributeChangedSingature OnMaxHealthChanged;
protected:
	void HandleHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleMaxHealthChanged(const FOnAttributeChangeData& Data) const;
};
