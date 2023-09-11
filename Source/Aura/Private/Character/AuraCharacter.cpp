// Copyright Yang Dong


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Data/AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Algo/ForEach.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Input/AuraEnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
	: AutoMovementDestination(FVector::Zero()),
	  FollowTime(0),
	  ShortPressThreshold(.5),
	  bAutoMoving(false),
	  AutoRunAcceptanceRadius(50)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator{0, 400, 0};
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	Spline->bDrawDebug = false;
}

void AAuraCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const auto PlayerController = Cast<APlayerController>(GetController()))
	{
		check(InputMappingContext);

		if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AAuraCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bAutoMoving)
	{
		AutoMove();
	}
}

void AAuraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UAuraEnhancedInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(PlayerInputComponent);

	AuraEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);

	AuraEnhancedInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::HandleAbilityInput_Pressed, &ThisClass::HandleAbilityInput_Holding, &ThisClass::HandleAbilityInput_Released);
}

int32 AAuraCharacter::GetActorLevel()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetActorLevel();
}

void AAuraCharacter::InitAbilitySystemComponent()
{
	Super::InitAbilitySystemComponent();

	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	AbilitySystemComponent = AuraPlayerState->GetAuraAbilitySystemComponent();

	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
}

void AAuraCharacter::InitHUD()
{
	Super::InitHUD();

	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->Init(AuraPlayerController, AuraPlayerState, AbilitySystemComponent);
		}
	}
}

// Server Only
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 在这里能拿到 PlayerState ，见 APawn::PossessedBy
	InitAbilitySystem();
}

// Clients only
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 虽然理论上如果把 ASC 这个 UProperty 设置成 Replicated ，可以只在服务器上设置，但是
	// 这会导致在 UI 绑定委托时需要等 ASC 复制过来再执行，会更麻烦。
	InitAbilitySystem();
}


void AAuraCharacter::Move(const FInputActionValue& InputActionValue)
{
	const FRotator YawRotator{0, GetControlRotation().Yaw, 0};
	const FVector ForwardDirection = FRotationMatrix{YawRotator}.GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix{YawRotator}.GetUnitAxis(EAxis::Y);


	const FVector2D InputActionVector = InputActionValue.Get<FVector2D>();
	AddMovementInput(ForwardDirection, InputActionVector.Y);
	AddMovementInput(RightDirection, InputActionVector.X);
}

void AAuraCharacter::HandleAbilityInput_Pressed(const FGameplayTag InputTag)
{
}

void AAuraCharacter::HandleAbilityInput_Holding(const FGameplayTag InputTag)
{
	NULL_RETURN_VOID(GetAuraAbilitySystemComponent());

	const auto PlayerController = Cast<AAuraPlayerController>(GetController());
	NULL_RETURN_VOID(PlayerController);

	if (!InputTag.MatchesTagExact(FAuraGameplayTags::GetInputTagLMB()) || PlayerController->IsTargeting())
	{
		GetAuraAbilitySystemComponent()->OnAbilityInputHolding(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();


		if (PlayerController->GetCursorHit().bBlockingHit)
		{
			AutoMovementDestination = PlayerController->GetCursorHit().ImpactPoint;
		}

		const FVector Direction = (AutoMovementDestination - GetActorLocation()).GetSafeNormal();
		AddMovementInput(Direction);
	}
}

void AAuraCharacter::HandleAbilityInput_Released(const FGameplayTag InputTag)
{
	NULL_RETURN_VOID(GetAuraAbilitySystemComponent());

	const auto PlayerController = Cast<AAuraPlayerController>(GetController());
	NULL_RETURN_VOID(PlayerController);

	if (!InputTag.MatchesTagExact(FAuraGameplayTags::GetInputTagLMB()) || PlayerController->IsTargeting())
	{
		GetAuraAbilitySystemComponent()->OnAbilityInputReleased(InputTag);
	}
	else if (FollowTime < ShortPressThreshold)
	{
		if (UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, GetActorLocation(), AutoMovementDestination))
		{
			Spline->ClearSplinePoints();
			Algo::ForEach(NavigationPath->PathPoints, [this](const FVector& Location) { Spline->AddSplinePoint(Location, ESplineCoordinateSpace::World); });
			Spline->SetDrawDebug(true);
			AutoMovementDestination = NavigationPath->PathPoints.Last(0);
			bAutoMoving = true;
		}
	}

	FollowTime = 0;
}

void AAuraCharacter::AutoMove()
{
	const FVector Location = Spline->FindLocationClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
	const FVector Direction = Spline->FindDirectionClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);

	AddMovementInput(Direction);

	if (const float Distance = (Location - AutoMovementDestination).Length(); Distance < AutoRunAcceptanceRadius)
	{
		bAutoMoving = false;
		Spline->ClearSplinePoints();
		Spline->SetDrawDebug(false);
	}
}
