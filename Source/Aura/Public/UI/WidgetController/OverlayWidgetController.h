// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"


UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSingature, float, NewHealth);

	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnHealthChangedSingature OnHealthChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSingature, float, NewMaxHealth);

	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnMaxHealthChangedSingature OnMaxHealthChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSingature, float, NewMana);

	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnManaChangedSingature OnManaChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSingature, float, NewMaxMana);

	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnMaxManaChangedSingature OnMaxManaChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
