// Copyright Yang Dong


#include "Player/AuraPlayerController.h"

#include "Aura/Aura.h"
#include "Interaction/EnemyInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Navigation/PathFollowingComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	bEnableMouseOverEvents = true;

	PathFollowingComponent = CreateDefaultSubobject<UPathFollowingComponent>("PathFollowingComponent");
}

void AAuraPlayerController::GetInteractiveHit(FHitResult& InteractiveHit) const
{
	GetHitResultUnderCursor(EAuraCollisionChannel::Interactivity, false, InteractiveHit);
}

bool AAuraPlayerController::IsTargetingEnemy(const FHitResult& Hit) const
{
	return Hit.bBlockingHit && Hit.GetActor()->Implements<UEnemyInterface>();
}

bool AAuraPlayerController::IsTargetingEnemy() const
{
	FHitResult Hit;
	GetInteractiveHit(Hit);
	return IsTargetingEnemy(Hit);
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
