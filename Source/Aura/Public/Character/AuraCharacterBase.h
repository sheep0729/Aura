// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAuraAttributeSet;
class UAuraAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAuraAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent() const override;

	TObjectPtr<UAuraAttributeSet> GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	virtual void InitAbility();

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level) const;

	void InitialAttributes() const;

	UPROPERTY(EditAnywhere, Category="Aura|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Aura|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Aura|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributesEffect;
};
