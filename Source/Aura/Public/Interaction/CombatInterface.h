// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CombatInterface.generated.h"

class UAnimMontage;

// 这个结构体是必要的，如果直接用 TMap 存储，随机访问性能较差
USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage;
};

UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:

	virtual int32 GetActorLevel() const PURE_VIRTUAL(ICombatInterface::GetActorLevel, return -1;);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);
	
	virtual void Die() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetFacingTarget(const FVector& TargetLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetMontages(TArray<FTaggedMontage>& OutMontages);
};
