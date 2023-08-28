// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSingature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSingature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSingature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSingature, float, NewMaxMana);

USTRUCT()
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIMessageSingature, const FUIWidgetRow&, Row);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnHealthChangedSingature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnMaxHealthChangedSingature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnManaChangedSingature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnMaxManaChangedSingature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Messages")
	FOnUIMessageSingature OnUIMessage;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aura|Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
};
