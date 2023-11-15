// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UObject/StrongObjectPtr.h"
#include "Marco.h"
#include "AuraEnemy.generated.h"

class AAuraAIController;
struct FGameplayEffectContext;
class UFloatingDamageComponent;
struct FGameplayTag;
class UEnemyWidgetController;
class UWidgetComponent;

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
    GENERATED_BODY()

public:
    AAuraEnemy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
    
    virtual void BeginPlay() override;
    
    virtual void Die() override;
    
    /* Combat Interface */
    virtual int32 GetActorLevel() const override
    {
        return ActorLevel;
    }
    /* Combat Interface */

    /* Enemy Interface */
    UFUNCTION()
    virtual void HighlightActor(UPrimitiveComponent* TouchedComponent) override;

    UFUNCTION()
    virtual void UnhighlightActor(UPrimitiveComponent* TouchedComponent) override;

    virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;

    virtual AActor* GetCombatTarget_Implementation() override;
    /* Enemy Interface */
    
    VALUE_GETTER_FUNC_NAME(bHighlighted, IsHighlighted);
    SETTER_FUNC_NAME(bHighlighted, SetHighlighted);

    VALUE_GETTER_FUNC_NAME(bHitReacting, IsHitReacting);

protected:
    virtual void InitAbilitySystemComponent() override;

    virtual void InitUI() override;

    UFUNCTION()
    void OnHitReactTagChanged(const FGameplayTag Tag, int32 Count);

    AAuraAIController* GetAIController() const;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom|Character Class Defults")
    int32 ActorLevel;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UWidgetComponent> HealthBar;

    UPROPERTY(EditAnywhere, Instanced)
    TObjectPtr<UEnemyWidgetController> WidgetController;
    
    UPROPERTY()
    bool bHitReacting;

    UPROPERTY()
    bool bHighlighted;

    UPROPERTY()
    int LifeSpanAfterDeath;

private:
    
    UPROPERTY(BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess))
    TObjectPtr<AActor> CombatTarget;
};