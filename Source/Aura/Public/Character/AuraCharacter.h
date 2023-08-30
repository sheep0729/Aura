// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void BeginPlay() override;

	/* Combat Interface */
	virtual int32 GetActorLevel() override;
	/* Combat Interface */
protected:
	virtual void InitAbility() override;
private:
	
};
