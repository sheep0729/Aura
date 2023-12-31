﻿// Copyright Yang Dong


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilityType.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AI/AuraAIController.h"
#include "Aura/Aura.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/EnemyWidgetController.h"
#include "Data/AuraGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AAuraEnemy::AAuraEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  ActorLevel(1),
	  LifeSpanAfterDeath(5)
{
	GetMesh()->SetCollisionProfileName(EAuraCollisionProfileName::Enemy);
	// GetCapsuleComponent()->SetCollisionProfileName(EAuraCollisionProfileName::Enemy);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
	HealthBar->SetRelativeLocation(FVector{0, 0, 60});
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);

	WidgetController = CreateDefaultSubobject<UEnemyWidgetController>("WidgetController");

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCustomDepthStencilValue(CustomDepth::Red);
	Weapon->SetCustomDepthStencilValue(CustomDepth::Red);

	GetCapsuleComponent()->OnBeginCursorOver.AddDynamic(this, &ThisClass::HighlightActor);
	GetCapsuleComponent()->OnEndCursorOver.AddDynamic(this, &ThisClass::UnhighlightActor);

	InitAbilitySystem();

	// OnDestroyed.AddDynamic(this, &ThisClass::PrintDestroyed);
}

void AAuraEnemy::InitAbilitySystemComponent()
{
	Super::InitAbilitySystemComponent();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Effect_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this,
		&AAuraEnemy::OnHitReactTagChanged
	);
}

void AAuraEnemy::InitUI()
{
	Super::InitUI();

	INVALID_RETURN_VOID(WidgetController);

	WidgetController->Initialize(AbilitySystemComponent);

	const auto HealthBarWidget = HealthBar->GetUserWidgetObject();
	INVALID_RETURN_VOID(HealthBarWidget);

	// UserWidget Component 直到 BeginPlay 才初始化自己的 Widget
	Cast<UAuraUserWidget>(HealthBarWidget)->SetWidgetController(WidgetController);
}

void AAuraEnemy::HighlightActor(UPrimitiveComponent* TouchedComponent)
{
	SetHighlighted(true);

	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnhighlightActor(UPrimitiveComponent* TouchedComponent)
{
	SetHighlighted(false);

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AAuraEnemy::GetCombatTarget_Implementation()
{
	return CombatTarget;
}

void AAuraEnemy::Die()
{
	Super::Die();

	SetLifeSpan(LifeSpanAfterDeath);
	if (GetAIController())
		GetAIController()->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);
	// HealthBar->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void AAuraEnemy::OnHitReactTagChanged(const FGameplayTag Tag, int32 Count)
{
	bHitReacting = Count != 0;
}

AAuraAIController* AAuraEnemy::GetAIController() const
{
	const auto MyController = GetController();
	INVALID_RETURN_OBJECT(MyController, nullptr);

	return Cast<AAuraAIController>(MyController);
}

void AAuraEnemy::PrintDestroyed(AActor* Actor)
{
	UKismetSystemLibrary::PrintString(this, FString::Format(TEXT("{1} Destroyed."), {GetNameSafe(Actor)}));
}
