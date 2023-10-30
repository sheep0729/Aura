#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AuraAIController.generated.h"

struct FGameplayTag;
class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class AURA_API AAuraAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAuraAIController();

	virtual void OnPossess(APawn* InPawn) override;

protected:

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UFUNCTION()
	void OnHitReactTagChanged(const FGameplayTag Tag, int32 Count);
};
