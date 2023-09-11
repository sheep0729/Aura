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
	virtual void PlayerTick(float DeltaTime) override;

	bool IsTargeting() const {return ThisActor != nullptr;}

	CONST_REF_GETTER(CursorHit);

	bool IsTargetingEnemy() const;

	VALUE_GETTER(PathFollowingComponent);
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TObjectPtr<UPathFollowingComponent> PathFollowingComponent;
};
