// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "DamageGameplayAbility.generated.h"


UCLASS()
class AURA_API UDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:

	CONST_REF_GETTER(DamageMap);
	CONST_REF_GETTER(DamageEffectClass);

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess))
	TMap<FGameplayTag, FScalableFloat> DamageMap;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom|Projectile", meta = (AllowPrivateAccess))
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
