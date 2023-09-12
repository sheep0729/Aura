// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeInfoSingature, const FAuraAttributeInfo&, Info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributeMenuClosedSingature);

UCLASS()
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "Custom|GAS|Attributes")
	FOnAttributeInfoSingature OnAttributeInfo;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Custom|GAS|Messages")
	FOnAttributeMenuClosedSingature OnAttributeMenuClosed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Custom|GAS|Messages")
	FOnAttributeMenuClosedSingature OnClickedAttributeMenuButton;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfoData;

	void HandleAttributeValueChanged(const FOnAttributeChangeData& Data);

	const FAuraAttributeInfo& GetAttributeInfo(const FGameplayAttribute& Attribute);
};
