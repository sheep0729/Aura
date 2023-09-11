// Copyright Yang Dong


#include "Player/AuraPlayerController.h"

#include "Aura/Aura.h"
#include "Interaction/EnemyInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Navigation/PathFollowingComponent.h"

AAuraPlayerController::AAuraPlayerController()
	: LastActor(nullptr),
	  ThisActor(nullptr)

{
	bReplicates = true;
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

#if WITH_EDITOR
	UKismetSystemLibrary::ExecuteConsoleCommand(this, "show splines", this);
#endif
}

void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)
	{
		return;
	}

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor != ThisActor)
	{
		if (ThisActor)
		{
			ThisActor->HighlightActor();
		}

		if (LastActor)
		{
			LastActor->UnHighlightActor();
		}
	}
}
