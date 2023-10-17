// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Marco.h"
#include "Engine/DataAsset.h"
#include "AuraCharacterInfo.generated.h"

class UGameplayEffect;
class UAnimMontage;
class UGameplayAbility;

UENUM(BlueprintType)
enum class EAuraCharacterClass : uint8
{
	None,
	Aura,
	Elementalist,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FAuraCharacterInfo
{
	GENERATED_BODY()

	REF_GETTER(AttributeEffects);
	CONST_REF_GETTER(AttributeEffects);

	REF_GETTER(Abilities);
	CONST_REF_GETTER(Abilities);

	//CONST_VALUE_GETTER(HitReactMontage);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Default Attribute Effects")
	TArray<TSubclassOf<UGameplayEffect>> AttributeEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Default Abilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
};

UCLASS()
class AURA_API UAuraCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
	const FAuraCharacterInfo& GetCharacterInfo(EAuraCharacterClass CharacterClass);

	CONST_REF_GETTER(DamageCalculationCoefficients);
protected:
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	virtual void PostLoad() override;

	void FillDefaultValues();
	void FillDefaultValues(FAuraCharacterInfo& Data);

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	FAuraCharacterInfo DefaultCharacterInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TMap<EAuraCharacterClass, FAuraCharacterInfo> CharacterInfoMap;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;
};
