// Copyright Yang Dong


#include "AbilitySystem/ExecutionCalculation/GEEC_Damage.h"

#include "AbilitySystemComponent.h"
#include "Marco.h"
#include "AbilitySystem/AuraAbilitySystemNativeLibrary.h"
#include "Data/AuraGameplayTags.h"

// Alternate DEFINE_ATTRIBUTE_CAPTUREDEF
#define DEFINE_ATTRIBUTE_CAPTURE_DEF(AttributeSet, AttributeName, From, bSnapshot) \
{ \
	AttributeName##Property = AttributeSet::Get##AttributeName##Property(); \
	AttributeName##Def = FGameplayEffectAttributeCaptureDefinition(AttributeName##Property, EGameplayEffectAttributeCaptureSource::From, bSnapshot); \
}

struct FAuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	
	FAuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTURE_DEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTURE_DEF(UAuraAttributeSet, BlockChance, Target, false);
	}

	static const FAuraDamageStatics& Get()
	{
		static FAuraDamageStatics Singleton;
		return Singleton;
	}
};

UGEEC_Damage::UGEEC_Damage()
{
	RelevantAttributesToCapture.Add(FAuraDamageStatics::Get().ArmorDef);
	RelevantAttributesToCapture.Add(FAuraDamageStatics::Get().BlockChanceDef);
}

void UGEEC_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                          FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	INVALID_RETURN_VOID(SourceASC);
	
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	INVALID_RETURN_VOID(TargetASC);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	auto [SourceTags, TargetTags] = AuraAbilitySystemNativeLibrary::GetAllAggregatedTagsFromGameplayEffectSpec(Spec);

	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = SourceTags;
	AggregatorEvaluateParameters.TargetTags = TargetTags;

	// 获取计算需要捕获的 Attribute 的 Magnitude
	// float ArmorMagnitude = 0;
	// ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FAuraDamageStatics::Get().ArmorDef, AggregatorEvaluateParameters, ArmorMagnitude);
	// ArmorMagnitude = FMath::Max(0, ArmorMagnitude);
	// Custom Calculation，可以修改多个属性
	// 注意：只有 instant 和 periodic 的 GE 可以使用 Execution Calculation，也就是说 GEEC 改变的是 BaseValue
	// const FGameplayModifierEvaluatedData EvaluatedData(FAuraDamageStatics::Get().ArmorProperty, EGameplayModOp::Additive, ArmorMagnitude);
	
	// 获取 SetByCaller 的 Magnitude ，如果没找到会返回 0
	float DamageMagnitude = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::GetEffectTagDamage());

	// Capture BlockChance on Target, and determine if there was a successful Block
	float TargetBlockChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FAuraDamageStatics::Get().BlockChanceDef, AggregatorEvaluateParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max(0, TargetBlockChance);

	// if Block, halve the damage.
	if (const bool bBlocked = FMath::RandRange(1, 100) <= TargetBlockChance; bBlocked)
	{
		DamageMagnitude *= 0.5;
	}
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, DamageMagnitude);
	
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
