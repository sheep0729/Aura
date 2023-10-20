// Copyright Yang Dong


#include "AbilitySystem/ExecutionCalculation/GEEC_Damage.h"

#include "AbilitySystemComponent.h"
#include "Marco.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAbilitySystemNativeLibrary.h"
#include "AbilitySystem/AuraAbilityType.h"
#include "Data/AuraGameplayTags.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

// Alternate DEFINE_ATTRIBUTE_CAPTUREDEF
#define DEFINE_ATTRIBUTE_CAPTURE_DEF(AttributeSet, AttributeName, From, bSnapshot) \
{ \
	AttributeName##Property = AttributeSet::Get##AttributeName##Property(); \
	AttributeName##Def = FGameplayEffectAttributeCaptureDefinition(AttributeName##Property, EGameplayEffectAttributeCaptureSource::From, bSnapshot); \
}

struct FAuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	
	FAuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTURE_DEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTURE_DEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTURE_DEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTURE_DEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTURE_DEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTURE_DEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
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
	RelevantAttributesToCapture.Add(FAuraDamageStatics::Get().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(FAuraDamageStatics::Get().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(FAuraDamageStatics::Get().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(FAuraDamageStatics::Get().CriticalHitDamageDef);
}

void UGEEC_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                          FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	INVALID_RETURN_VOID(SourceASC);

	AActor* SourceAvatar = SourceASC->GetAvatarActor();
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	INVALID_RETURN_VOID(TargetASC);

	AActor* TargetAvatar = TargetASC->GetAvatarActor();
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

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

	// 获取 Effect Context
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	FAuraGameplayEffectContext* EffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get());

	// 半伤

	float TargetBlockChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FAuraDamageStatics::Get().BlockChanceDef, AggregatorEvaluateParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max(0, TargetBlockChance);

	const bool bBlocked = FMath::RandRange(1, 100) <= TargetBlockChance;
	EffectContext->SetIsBlockHit(bBlocked);
	if (bBlocked)
	{
		DamageMagnitude *= 0.5;
	}

	const auto DamageCalculationCoefficients = UAuraAbilitySystemLibrary::GetDamageCalculationCoefficients(SourceAvatar);

	// 护甲穿透：忽略百分比护甲
	
	const FRealCurve* ArmorPenetrationCurve = DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString{});
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetActorLevel());
	const FRealCurve* EffectiveArmorCurve = DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString{});
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetActorLevel());
	// UKismetSystemLibrary::PrintString(SourceAvatar, FString::Format(TEXT("Source Armor Penetration Coefficient = [{0}]\nTarget Effective Armor Coefficient = [{1}]"), {ArmorPenetrationCoefficient, EffectiveArmorCoefficient}));
	
	float TargetArmor = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FAuraDamageStatics::Get().ArmorDef, AggregatorEvaluateParameters, TargetArmor);
	TargetArmor = FMath::Max(0, TargetArmor);

	float SourceArmorPenetration = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FAuraDamageStatics::Get().ArmorPenetrationDef, AggregatorEvaluateParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max(0, SourceArmorPenetration);

	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100;
	DamageMagnitude *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100;

	// 暴击
	float SourceCriticalHitChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FAuraDamageStatics::Get().CriticalHitChanceDef, AggregatorEvaluateParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max(0, SourceCriticalHitChance);

	float TargetCriticalHitResistance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FAuraDamageStatics::Get().CriticalHitResistanceDef, AggregatorEvaluateParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max(0, TargetCriticalHitResistance);

	const FRealCurve* CriticalHitResistanceCurve = DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString{});
	const float CriticalHitResistance = CriticalHitResistanceCurve->Eval(TargetCombatInterface->GetActorLevel());
	
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistance;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;

	EffectContext->SetIsCriticalHit(bCriticalHit);
	if (bCriticalHit)
	{
		float SourceCriticalHitDamage = 0;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FAuraDamageStatics::Get().CriticalHitDamageDef, AggregatorEvaluateParameters, SourceCriticalHitDamage);
		SourceCriticalHitDamage = FMath::Max(0, SourceCriticalHitDamage);

		DamageMagnitude = 2 * DamageMagnitude + SourceCriticalHitDamage;
	}
	

	// Output Modifier
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, DamageMagnitude);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
