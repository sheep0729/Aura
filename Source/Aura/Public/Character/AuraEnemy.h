// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UObject/StrongObjectPtr.h"
#include "Marco.h"
#include "AuraEnemy.generated.h"

class UEnemyWidgetController;
class UWidgetComponent;

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
    GENERATED_BODY()

public:
    AAuraEnemy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UFUNCTION()
    virtual void HighlightActor(UPrimitiveComponent* TouchedComponent) override;

    UFUNCTION()
    virtual void UnhighlightActor(UPrimitiveComponent* TouchedComponent) override;

    virtual void BeginPlay() override;

    /* Combat Interface */
    virtual int32 GetActorLevel() const override
    {
        return ActorLevel;
    }

    /* Combat Interface */

    UFUNCTION(BlueprintCallable)
    bool IsHighlighted() const
    {
        return bHighlighted;
    }

    void SetHighlighted(bool InBool)
    {
        bHighlighted = InBool;
    }

    UFUNCTION()
    bool IsHitReacting() const
    {
        return bHitReacting;
    }

protected:
    virtual void InitAbilitySystemComponent() override;

    virtual void InitUI() override;

    UFUNCTION()
    void OnHitReact(const FGameplayTag Tag, int32 Count);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom|Character Class Defults")
    int32 ActorLevel;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UWidgetComponent> HealthBar;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UEnemyWidgetController> WidgetController;

    UPROPERTY()
    bool bHitReacting;

    UPROPERTY()
    bool bHighlighted;
};