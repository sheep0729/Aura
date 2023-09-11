// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Marco.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "AuraPlayerController.generated.h"

class UPathFollowingComponent;
class USplineComponent;
struct FGameplayTag;
class UAuraInputConfig;
class IEnemyInterface;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	void GetInteractiveHit(FHitResult& InteractiveHit) const;

	bool IsTargetingEnemy(const FHitResult& Hit) const;

	bool IsTargetingEnemy() const;

	VALUE_GETTER(PathFollowingComponent);
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TObjectPtr<UPathFollowingComponent> PathFollowingComponent;
};
