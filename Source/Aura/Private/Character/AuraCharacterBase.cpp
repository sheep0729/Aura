// Copyright Yang Dong


#include "Character/AuraCharacterBase.h"

#include "MotionWarpingComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Character/AuraCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"  // Rider bug
#include "Data/AuraCharacterInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Game/AuraGameStateBase.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Data/AuraGameplayTags.h"

AAuraCharacterBase::AAuraCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass(CharacterMovementComponentName, UAuraCharacterMovementComponent::StaticClass())),
	  bDead(false)
{
	PrimaryActorTick.bCanEverTick = false;
	
	bCanAffectNavigationGeneration = true;
	GetCapsuleComponent()->SetCanEverAffectNavigation(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionProfileName(EAuraCollisionProfileName::Weapon);

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
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
	return UAuraAbilitySystemLibrary::GetCharacterInfo(this, CharacterClass);
}

void AAuraCharacterBase::InitAbilitySystemComponent()
{
}

void AAuraCharacterBase::PostInitAbilitySystemComponent()
{
	if (HasAuthority())
	{
		AbilitySystemComponent->GetOnDamaged().AddDynamic(this, &ThisClass::HandleDamaged); // 在 Server 上发起 Die
	}
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
	GetController()->UnPossess();
	
	MulticastHandleDeath();
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules{EDetachmentRule::KeepWorld, true});
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();

	bDead = true;
}

FVector AAuraCharacterBase::GetWeaponFireSocketLocation_Implementation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponFireSocketName);
}

bool AAuraCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AAuraCharacterBase::GetAvatar_Implementation()
{
	return this;
}

void AAuraCharacterBase::HandleDamaged(float Damage, float OldHealth, float NewHealth, const FGameplayEffectContextHandle EffectContextHandle)
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

void AAuraCharacterBase::Dissolve()
{
	TArray<UMaterialInstanceDynamic*> DynamicMaterials;
	DynamicMaterials.Add(SetDynamicDissolveMaterial(GetMesh(), DissolveMaterialInstance));
	DynamicMaterials.Add(SetDynamicDissolveMaterial(Weapon, WeaponDissolveMaterialInstance));
	StartDissolveTimeline(DynamicMaterials);
}

UMaterialInstanceDynamic* AAuraCharacterBase::SetDynamicDissolveMaterial(USkeletalMeshComponent* InMesh, UMaterialInstance* MaterialInstance)
{
	const auto MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialInstance, InMesh);
	InMesh->SetMaterial(0, MaterialInstanceDynamic);
	return MaterialInstanceDynamic;
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReact;
}

void AAuraCharacterBase::SetFacingTarget_Implementation(const FVector& TargetLocation)
{
	ICombatInterface::SetFacingTarget_Implementation(TargetLocation);

	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation("FacingTarget", TargetLocation);
}
