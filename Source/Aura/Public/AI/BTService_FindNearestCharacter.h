// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearestCharacter.generated.h"

UCLASS()
class AURA_API UBTService_FindNearestCharacter : public UBTService_BlueprintBase
{
	GENERATED_BODY()

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess))
	FBlackboardKeySelector TargetToFollow;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess))
	FBlackboardKeySelector DistanceToTarget;
};
