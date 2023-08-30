// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Marco.h"
#include "AbilitySystem/AuraAbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAuraAttributeSet;
class UAuraAbilitySystemComponent;

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAuraAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent() const override;

	UAuraAttributeSet* GetAuraAttributeSet() const { return AttributeSet; }

	VALUE_GETTER(ActorLevel);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;

private:
	UFUNCTION()
	void OnRep_ActorLevel(int32 OldLevel);
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_ActorLevel, Category = "Aura")
	int32 ActorLevel;
};
