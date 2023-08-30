// Copyright Yang Dong


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
	:ActorLevel(1)
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitAbility();
}

void AAuraEnemy::HighlightActor()
{
	SetHighlighted(true);

	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	SetHighlighted(false);

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCustomDepthStencilValue(CustomDepthRed);
	Weapon->SetCustomDepthStencilValue(CustomDepthRed);
}

void AAuraEnemy::InitAbility()
{
	Super::InitAbility();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
