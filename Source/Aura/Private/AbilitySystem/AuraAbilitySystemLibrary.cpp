// Copyright Yang Dong


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Data/AuraGameplayTags.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "Marco.h"
#include "AbilitySystem/AuraAbilityType.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Game/AuraGameStateBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"

const TArray<FGameplayTag>& UAuraAbilitySystemLibrary::GetPrimaryAttributeTags()
{
	return FAuraGameplayTags::GetPrimaryAttributeTags();
}

const TArray<FGameplayTag>& UAuraAbilitySystemLibrary::GetSecondaryAttributeTags()
{
	return FAuraGameplayTags::GetSecondaryAttributeTags();
}

const FGameplayAttribute& UAuraAbilitySystemLibrary::GetAttributesByTag(const FGameplayTag& AttributeTag)
{
	const auto AttributePtr = FAuraGameplayTags::GetAttributeMap().Find(AttributeTag);
	check(AttributePtr);
	return *AttributePtr;
}

FString UAuraAbilitySystemLibrary::GetAttributeName(const FGameplayAttribute& Attribute)
{
	return Attribute.AttributeName;
}

const TArray<FGameplayAttribute>& UAuraAbilitySystemLibrary::GetAttributes()
{
	return UAuraAttributeSet::GetAttributes();
}

const TArray<FGameplayAttribute>& UAuraAbilitySystemLibrary::GetPrimaryAttributes()
{
	return UAuraAttributeSet::GetPrimaryAttributes();
}

const TArray<FGameplayAttribute>& UAuraAbilitySystemLibrary::GetSecondaryAttributes()
{
	return UAuraAttributeSet::GetSecondaryAttributes();
}

const FAuraCharacterInfo& UAuraAbilitySystemLibrary::GetCharacterInfo(const UObject* WorldContextObject, const EAuraCharacterClass CharacterClass)
{
	const auto GameState = CastChecked<AAuraGameStateBase>(UGameplayStatics::GetGameState(WorldContextObject));
	return GameState->GetCharacterInfo(CharacterClass);
}

const UCurveTable* UAuraAbilitySystemLibrary::GetDamageCalculationCoefficients(const UObject* WorldContextObject)
{
	const auto GameState = CastChecked<AAuraGameStateBase>(UGameplayStatics::GetGameState(WorldContextObject));
	return GameState->GetDamageCalculationCoefficients();
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* EffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()); EffectContext)
	{
		return EffectContext->IsBlockHit();
	}

	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* EffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()); EffectContext)
	{
		return EffectContext->IsCriticalHit();
	}

	return false;
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockHit)
{
	if (FAuraGameplayEffectContext* EffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()); EffectContext)
	{
		EffectContext->SetIsBlockHit(bInIsBlockHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FAuraGameplayEffectContext* EffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()); EffectContext)
	{
		EffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UAuraAbilitySystemLibrary::GetLivePlayerWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors,
	const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (const auto OverlappedActor = Overlap.GetActor(); OverlappedActor->Implements<UCombatInterface>())
			{
				if (!ICombatInterface::Execute_IsDead(OverlappedActor))
				{
					OutOverlappingActors.AddUnique(OverlappedActor);
				}
			}
		}
	}
}
