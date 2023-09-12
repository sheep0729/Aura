// Copyright Yang Dong


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/EnemyWidgetController.h"

AAuraEnemy::AAuraEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), ActorLevel(1), WidgetControllerClass(UEnemyWidgetController::StaticClass())
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	WidgetController = Cast<UEnemyWidgetController>(
		CreateDefaultSubobject("WidgetController", WidgetControllerClass, WidgetControllerClass, true, false)
	);

	GetCapsuleComponent()->SetCollisionProfileName(EAuraCollisionProfileName::Enemy);
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

	InitAbilitySystem();
}

void AAuraEnemy::InitAbilitySystemComponent()
{
	Super::InitAbilitySystemComponent();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AAuraEnemy::InitUI()
{
	Super::InitUI();

	WidgetController->Initialize(AbilitySystemComponent);
	Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject())->SetWidgetController(WidgetController);
}
