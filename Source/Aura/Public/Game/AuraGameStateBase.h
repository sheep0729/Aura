// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AuraGameStateBase.generated.h"

enum class EAuraCharacterClass : uint8;
struct FAuraCharacterInfo;
class UAuraCharacterData;

UCLASS()
class AURA_API AAuraGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	const FAuraCharacterInfo& GetCharacterInfo(EAuraCharacterClass CharacterClass) const;
	const UCurveTable* GetDamageCalculationCoefficients() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TObjectPtr<UAuraCharacterData> CharacterData;
};
