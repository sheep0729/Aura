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

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
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
