// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/HUD/AuraHUD.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;

UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|Attributes")
	static const TArray<FGameplayTag>& GetPrimaryAttributeTags();

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|Attributes")
	static const TArray<FGameplayTag>& GetSecondaryAttributeTags();

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|Attributes")
	static const FGameplayAttribute& GetAttributesByTag(const FGameplayTag& AttributeTag);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|Attributes")
	static FString GetAttributeName(const FGameplayAttribute& Attribute);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|Attributes")
	static const TArray<FGameplayAttribute>& GetAttributes();

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|Attributes")
	static const TArray<FGameplayAttribute>& GetPrimaryAttributes();

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|Attributes")
	static const TArray<FGameplayAttribute>& GetSecondaryAttributes();
};
