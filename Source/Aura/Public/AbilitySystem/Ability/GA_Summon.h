// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "GA_Summon.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UGA_Summon : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Summoning")
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Summoning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Summoning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Summoning")
	float SpawnSpread = 90.f;
};
