// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void HighlightActor(UPrimitiveComponent* TouchedComponent) override;
	
	UFUNCTION()
	virtual void UnhighlightActor(UPrimitiveComponent* TouchedComponent) override;

	virtual void BeginPlay() override;

	/* Combat Interface */
	virtual int32 GetActorLevel() override
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

protected:
	virtual void InitAbilitySystemComponent() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aura|Character Class Defults")
	int32 ActorLevel;

private:
	bool bHighlighted;
};
