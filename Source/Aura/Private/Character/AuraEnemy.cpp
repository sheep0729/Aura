// Copyright Yang Dong


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"

AAuraEnemy::AAuraEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), ActorLevel(1)
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void AAuraEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitAbilitySystem();
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

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCustomDepthStencilValue(CustomDepth::Red);
	Weapon->SetCustomDepthStencilValue(CustomDepth::Red);

	GetCapsuleComponent()->OnBeginCursorOver.AddDynamic(this, &ThisClass::HighlightActor);
	GetCapsuleComponent()->OnEndCursorOver.AddDynamic(this, &ThisClass::UnhighlightActor);
}

void AAuraEnemy::InitAbilitySystemComponent()
{
	Super::InitAbilitySystemComponent();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
