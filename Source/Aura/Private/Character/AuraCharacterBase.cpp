// Copyright Yang Dong


#include "Character/AuraCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Character/AuraCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"  // Rider bug
#include "Data/AuraCharacterInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Game/AuraGameStateBase.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Data/AuraGameplayTags.h"

AAuraCharacterBase::AAuraCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass(CharacterMovementComponentName, UAuraCharacterMovementComponent::StaticClass()))
{
	PrimaryActorTick.bCanEverTick = false;

	bCanAffectNavigationGeneration = true;
	GetCapsuleComponent()->SetCanEverAffectNavigation(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionProfileName(EAuraCollisionProfileName::Weapon);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return GetAuraAbilitySystemComponent();
}

UAuraAbilitySystemComponent* AAuraCharacterBase::GetAuraAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacterBase::InitAbilitySystem()
{
	InitAbilitySystemComponent();
	INVALID_RETURN_VOID(GetAuraAbilitySystemComponent());
	PostInitAbilitySystemComponent();

	InitUI();

	if (HasAuthority())
	{
		InitAttributes(); // 也可以同时在 Client 上初始化，反正是复制的
		InitAbilities();
	}
}

const FAuraCharacterInfo& AAuraCharacterBase::GetCharacterInfo() const
{
	const auto GameState = CastChecked<AAuraGameStateBase>(UGameplayStatics::GetGameState(this));
	return GameState->GetCharacterInfo(CharacterClass);
}

void AAuraCharacterBase::InitAbilitySystemComponent()
{
}

void AAuraCharacterBase::PostInitAbilitySystemComponent()
{
	AbilitySystemComponent->GetOnDamaged().AddUObject(this, &ThisClass::HandleDamaged);
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(Effect);

	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); // 如果这里不设置，MMC 中拿不到 SourceObject

	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(Effect, Level, EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data, GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitAttributes() const
{
	for (const auto& AttributeEffect : GetCharacterInfo().GetAttributeEffects())
	{
		ApplyEffectToSelf(AttributeEffect, GetActorLevel());
	}
}

void AAuraCharacterBase::InitUI()
{
}

void AAuraCharacterBase::InitAbilities()
{
	for (const auto& Ability : GetCharacterInfo().GetAbilities())
	{
		AbilitySystemComponent->GiveAbility(Ability, 1);
	}
}

void AAuraCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules{EDetachmentRule::KeepWorld, true});
	MulticastHandleDeath();
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

FVector AAuraCharacterBase::GetWeaponFireSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponFireSocketName);
}

void AAuraCharacterBase::HandleDamaged(float Damage, float OldHealth, float NewHealth)
{
	if (NewHealth == 0)
	{
		Die();
	}
	else
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer{FAuraGameplayTags::GetEffectTagHitReact()});
	}
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReact;
}
