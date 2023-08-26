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
	AAuraEnemy();
	virtual void PostInitializeComponents() override;
	
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	virtual void BeginPlay() override;

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
	virtual void InitAbility() override;
private:
	bool bHighlighted;
};
