// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSingature, float, NewValue);

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
	FOnAttributeChangedSingature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnAttributeChangedSingature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnAttributeChangedSingature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Attributes")
	FOnAttributeChangedSingature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Aura|GAS|Messages")
	FOnUIMessageSingature OnUIMessage;

protected:
	void HandleHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleManaChanged(const FOnAttributeChangeData& Data) const;
	void HandleMaxManaChanged(const FOnAttributeChangeData& Data) const;

	UFUNCTION(Client, Reliable)
	void HandleMessageTags(FGameplayTagContainer MessageTags);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aura|Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
};
