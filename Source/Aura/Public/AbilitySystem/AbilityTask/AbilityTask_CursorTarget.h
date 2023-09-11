// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_CursorTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCursorTargetSingature, const FGameplayAbilityTargetDataHandle&, GameplayAbilityTargetDataHandle);

UCLASS()
class AURA_API UAbilityTask_CursorTarget : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName="CursorTarget",
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_CursorTarget* CreateCursorTargetProxy(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FOnCursorTargetSingature OnCursorTarget;

	virtual void Activate() override;

protected:

	void SendCursorTargetData();

	void HandleCursorDataReplicated(const FGameplayAbilityTargetDataHandle& GameplayAbilityTargetDataHandle, FGameplayTag ActivationTag);
};
