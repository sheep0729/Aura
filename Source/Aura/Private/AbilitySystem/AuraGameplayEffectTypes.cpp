#include "AbilitySystem/AuraGameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

FEffectActorInfo FEffectActorInfo::GetEffectActorInfo(UAbilitySystemComponent* AbilitySystemComponent)
{
	AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();
	ACharacter* AvatarCharacter = Cast<ACharacter>(AvatarActor);
	AController* Controller = AbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
	if (IsValid(Controller))
	{
		const APawn* AvatarPawn = Cast<APawn>(AvatarActor);
		Controller = AvatarPawn->GetController();
	}
	return FEffectActorInfo{AbilitySystemComponent, AvatarActor, AvatarCharacter, Controller};
}

FEffectContextData FEffectContextData::GetEffectContextData(const FGameplayEffectModCallbackData& Data)
{
	const FGameplayEffectContextHandle EffectContext = Data.EffectSpec.GetContext();
	const FEffectActorInfo Source = FEffectActorInfo::GetEffectActorInfo(EffectContext.GetOriginalInstigatorAbilitySystemComponent());
	const FEffectActorInfo Target = FEffectActorInfo::GetEffectActorInfo(&Data.Target);
	return FEffectContextData{EffectContext, Source, Target};
}
