// Copyright Yang Dong


#include "AbilitySystem/ModMagnitudeCalculation/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = SourceTags;
	AggregatorEvaluateParameters.TargetTags = TargetTags;

	float Vigor;
	GetCapturedAttributeMagnitude(VigorDef, Spec, AggregatorEvaluateParameters, Vigor);
	Vigor = FMath::Max(Vigor, 0);

	const ICombatInterface* CombatObject = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 ActorLevel = CombatObject->GetActorLevel();

	return 80 + 2.5 * Vigor + 10 * ActorLevel;
}
