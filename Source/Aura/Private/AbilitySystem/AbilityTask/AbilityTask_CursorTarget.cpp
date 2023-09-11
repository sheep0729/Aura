// Copyright Yang Dong


#include "AbilitySystem/AbilityTask/AbilityTask_CursorTarget.h"

#include "AbilitySystemComponent.h"
#include "Player/AuraPlayerController.h"

UAbilityTask_CursorTarget* UAbilityTask_CursorTarget::CreateCursorTargetProxy(UGameplayAbility* OwningAbility)
{
	const auto Obj = NewAbilityTask<UAbilityTask_CursorTarget>(OwningAbility);
	return Obj;
}

void UAbilityTask_CursorTarget::Activate()
{
	Super::Activate();

	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		SendCursorTargetData();
	}
	else
	{
		const FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle, ActivationPredictionKey).AddUObject(
			this, &ThisClass::HandleCursorDataReplicated);

		if (const bool bCalledDelegate = AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(AbilitySpecHandle, ActivationPredictionKey))
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UAbilityTask_CursorTarget::SendCursorTargetData()
{
	FScopedPredictionWindow ScopedPredictionWindow{AbilitySystemComponent.Get(), IsPredictingClient()};

	const TStrongObjectPtr PlayerController{
		Cast<AAuraPlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get())
	};

	FGameplayAbilityTargetData_SingleTargetHit* GameplayAbilityTargetData_SingleTargetHit = new FGameplayAbilityTargetData_SingleTargetHit();
	PlayerController->GetInteractiveHit(GameplayAbilityTargetData_SingleTargetHit->HitResult);

	FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
	GameplayAbilityTargetDataHandle.Add(GameplayAbilityTargetData_SingleTargetHit);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		GameplayAbilityTargetDataHandle,
		FGameplayTag::EmptyTag,
		AbilitySystemComponent->GetPredictionKeyForNewAction());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCursorTarget.Broadcast(GameplayAbilityTargetDataHandle);
	}
}

void UAbilityTask_CursorTarget::HandleCursorDataReplicated(
	const FGameplayAbilityTargetDataHandle& GameplayAbilityTargetDataHandle, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCursorTarget.Broadcast(GameplayAbilityTargetDataHandle);
	}
}
