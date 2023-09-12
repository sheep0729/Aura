// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

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

UCLASS()
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	
	UPROPERTY(BlueprintAssignable, Category = "Custom|GAS|Attributes")
	FOnAttributeChangedSingature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Custom|GAS|Attributes")
	FOnAttributeChangedSingature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Custom|GAS|Attributes")
	FOnAttributeChangedSingature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Custom|GAS|Attributes")
	FOnAttributeChangedSingature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Custom|GAS|Messages")
	FOnUIMessageSingature OnUIMessage;

protected:
	virtual void BindCallbacksToDependencies() override;
	
	void HandleHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleManaChanged(const FOnAttributeChangeData& Data) const;
	void HandleMaxManaChanged(const FOnAttributeChangeData& Data) const;

	UFUNCTION(Client, Reliable)
	void HandleMessageTags(FGameplayTagContainer MessageTags);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aura|Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
};
