// Copyright Yang Dong


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Marco.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayPrediction.h"
#include "Algo/ForEach.h"


AAuraEffectActor::AAuraEffectActor()
	: bRefreshDurationOnApply(true),
	  EffectDuration(1)
{
	PrimaryActorTick.bCanEverTick = false;
	bDestroyOnApplied = true;
	bApplyToEnemy = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	check(GameplayEffectClass);
	FALSE_RETURN_VOID(!TargetActor->ActorHasTag(FName("Enemy")) || bApplyToEnemy);

	// UAbilitySystemComponent* TargetASC = Cast<IAbilitySystemInterface>(Target);
	UAuraAbilitySystemComponent* TargetASC = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	// 同样适用于没有实现接口的情况
	INVALID_RETURN_VOID(TargetASC);

	const auto TargetPawn = Cast<APawn>(TargetASC->GetAvatarActor());
	INVALID_RETURN_VOID(TargetPawn);

	FScopedPredictionWindow ScopedPredictionWindow{TargetASC, !TargetPawn->HasAuthority() && TargetPawn->IsLocallyControlled()};

	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContext);

	if (bRefreshDurationOnApply)
	{
		FGameplayEffectQuery CurrentEffect;
		CurrentEffect.EffectDefinition = GameplayEffectClass;

		const auto EffectHandles = TargetASC->GetActiveEffects(CurrentEffect);
		Algo::ForEach(EffectHandles, [this](const auto EffectHandle) { ActiveEffects.Remove(EffectHandle); });

		const auto TimeRemainings = TargetASC->GetActiveEffectsTimeRemaining(CurrentEffect);
		const float CurrentTimeRemaining = TimeRemainings.IsEmpty() ? 0 : TimeRemainings[0];

		TargetASC->RemoveActiveEffects(CurrentEffect, -1);
		
		EffectSpec.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("GameplayEffect.Duration"), CurrentTimeRemaining + EffectDuration);
	}

	const FActiveGameplayEffectHandle ActiveEffect = TargetASC->ApplyGameplayEffectSpecToSelf(
		*EffectSpec.Data, TargetASC->GetPredictionKeyForNewAction());

	if (EffectSpec.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite && InfiniteGameplayEffectRemovalPolicy ==
		EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffects.Add(ActiveEffect, TargetASC);
	}

	if (bDestroyOnApplied)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationGameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteGameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationGameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteGameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteGameplayEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		INVALID_RETURN_VOID(TargetASC);

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (const auto& Pair : ActiveEffects)
		{
			if (TargetASC == Pair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(Pair.Key, -1);
				HandlesToRemove.Add(Pair.Key);
			}
		}
		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffects.FindAndRemoveChecked(Handle);
		}
	}
}
