// Copyright Yang Dong


#include "AbilitySystem/ModMagnitudeCalculation/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = SourceTags;
	AggregatorEvaluateParameters.TargetTags = TargetTags;

	float Intelligence;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, AggregatorEvaluateParameters, Intelligence);
	Intelligence = FMath::Max(Intelligence, 0);

	ICombatInterface* CombatObject = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 ActorLevel = CombatObject->GetActorLevel();

	return 80 + 2.5 * Intelligence + 15 * ActorLevel;
}
