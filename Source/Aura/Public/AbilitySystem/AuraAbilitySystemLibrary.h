// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/HUD/AuraHUD.h"
#include "AuraAbilitySystemLibrary.generated.h"

enum class EAuraCharacterClass : uint8;
struct FAuraCharacterInfo;
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

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|Character")
	static const FAuraCharacterInfo& GetCharacterInfo(const UObject* WorldContextObject, const EAuraCharacterClass CharacterClass);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|Character")
	static const UCurveTable* GetDamageCalculationCoefficients(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	// 非 const 的引用默认会作为蓝图节点中的输出，想要让其作为输入需要 UPARAM(ref)
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockHit);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);
};
