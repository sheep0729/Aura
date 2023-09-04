// Copyright Yang Dong


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator{0, 400, 0};
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
}

int32 AAuraCharacter::GetActorLevel()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetActorLevel();
}

// Server Only
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 在这里能拿到 PlayerState ，见 APawn::PossessedBy
	InitAbility();
	InitializeAttributes(); // 也可以同时在 Client 上初始化，反正是复制的
}

// Clients only
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 虽然理论上如果把 ASC 这个 UProperty 设置成 Replicated ，可以只在服务器上设置，但是
	// 这会导致在 UI 绑定委托时需要等 ASC 复制过来再执行，会更麻烦。
	InitAbility(); 
}

void AAuraCharacter::InitAbility()
{
	Super::InitAbility();
	
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	
	AbilitySystemComponent = AuraPlayerState->GetAuraAbilitySystemComponent();

	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->Init(AuraPlayerController, AuraPlayerState, AbilitySystemComponent);
		}
	}
}
