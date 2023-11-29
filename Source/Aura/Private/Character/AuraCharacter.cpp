// Copyright Yang Dong


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Data/AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Input/AuraEnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer),
    bShiftKeyDown(false),
    Destination(FVector::Zero()),
    ShortPressThreshold(.5),
    FollowTime(0)
{
    PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator{ 0, 400, 0 };
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;
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

        if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
            PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void AAuraCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AAuraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UAuraEnhancedInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(PlayerInputComponent);

    AuraEnhancedInputComponent->BindNativeAction(InputConfig, FAuraGameplayTags::Input_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
    AuraEnhancedInputComponent->BindNativeAction(InputConfig, FAuraGameplayTags::Input_Shift, ETriggerEvent::Started, this,
        &ThisClass::ShiftPressed);
    AuraEnhancedInputComponent->BindNativeAction(InputConfig, FAuraGameplayTags::Input_Shift, ETriggerEvent::Completed, this,
        &ThisClass::ShiftReleased);

    AuraEnhancedInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::HandleAbilityInput_Pressed, &ThisClass::HandleAbilityInput_Holding,
        &ThisClass::HandleAbilityInput_Released);
}

int32 AAuraCharacter::GetActorLevel() const
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

void AAuraCharacter::InitUI()
{
    Super::InitUI();

    if (const AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
    {
        if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
        {
            AuraHUD->Initialize(AbilitySystemComponent);
        }
    }
}

bool AAuraCharacter::IsAbilityInput(const FGameplayTag& InputTag) const
{
    return !InputTag.MatchesTagExact(FAuraGameplayTags::Input_LMB) || Cast<AAuraPlayerController>(GetController())->IsTargetingEnemy() ||
        bShiftKeyDown;
}

// Server Only
void AAuraCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // 在这里能拿到 PlayerState ，见 APawn::PossessedBy
    InitAbilitySystem();

    INVALID_RETURN_VOID(GetAuraPlayerController());
    INVALID_RETURN_VOID(GetAuraPlayerController()->GetPathFollowingComponent());
    
    GetAuraPlayerController()->GetPathFollowingComponent()->Initialize();
}

void AAuraCharacter::OnRep_Controller()
{
    Super::OnRep_Controller();

    GetAuraPlayerController()->GetPathFollowingComponent()->Initialize();
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
    AbortMove();

    const FRotator YawRotator{ 0, GetControlRotation().Yaw, 0 };
    const FVector ForwardDirection = FRotationMatrix{ YawRotator }.GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix{ YawRotator }.GetUnitAxis(EAxis::Y);


    const FVector2D InputActionVector = InputActionValue.Get<FVector2D>();
    AddMovementInput(ForwardDirection, InputActionVector.Y);
    AddMovementInput(RightDirection, InputActionVector.X);
}

void AAuraCharacter::ShiftPressed()
{
    bShiftKeyDown = true;
}

void AAuraCharacter::ShiftReleased()
{
    bShiftKeyDown = false;
}

void AAuraCharacter::HandleAbilityInput_Pressed(const FGameplayTag InputTag)
{
    if (IsAbilityInput(InputTag))
    {
        AbortMove();
        GetAuraAbilitySystemComponent()->OnAbilityInputPressed(InputTag);
    }
}

void AAuraCharacter::HandleAbilityInput_Holding(const FGameplayTag InputTag)
{
    INVALID_RETURN_VOID(GetAuraAbilitySystemComponent());

    if (IsAbilityInput(InputTag))
    {
        AbortMove();
        GetAuraAbilitySystemComponent()->OnAbilityInputHolding(InputTag);
    }
    else
    {

        FollowTime += GetWorld()->GetDeltaSeconds();

        const auto PlayerController = Cast<AAuraPlayerController>(GetController());
        INVALID_RETURN_VOID(PlayerController);

        FHitResult InteractiveHit;
        PlayerController->GetInteractiveHit(InteractiveHit);
        if (InteractiveHit.bBlockingHit)
        {
            Destination = InteractiveHit.ImpactPoint;
        }

        const FVector Direction = (Destination - GetActorLocation()).GetSafeNormal();
        AddMovementInput(Direction);
    }
}

void AAuraCharacter::HandleAbilityInput_Released(const FGameplayTag InputTag)
{
    INVALID_RETURN_VOID(GetAuraAbilitySystemComponent());
    GetAuraAbilitySystemComponent()->OnAbilityInputReleased(InputTag); // tell ASC anyway

    if (!IsAbilityInput(InputTag) && FollowTime < ShortPressThreshold)
    {
        UKismetSystemLibrary::DrawDebugSphere(this, Destination, 8, 8, FLinearColor::Blue, 3, 1);
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Destination);
    }

    FollowTime = 0;
}

void AAuraCharacter::AbortMove()
{
    if (const auto PathFollowingComponent = GetAuraPlayerControllerChecked()->GetPathFollowingComponent())
    {
        PathFollowingComponent->AbortMove(*this, FPathFollowingResultFlags::UserAbort, FAIRequestID::AnyRequest, EPathFollowingVelocityMode::Reset);
    }
}
