// Copyright Yang Dong


#include "Character/AuraCharacterBase.h"

#include "MotionWarpingComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAbilitySystemNativeLibrary.h"
#include "Character/AuraCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"  // Rider bug
#include "Data/AuraCharacterInfo.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Character/FloatingDamageComponent.h"
#include "Data/AuraGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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

	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return GetAuraAbilitySystemComponent();
}

UAuraAbilitySystemComponent* AAuraCharacterBase::GetAuraAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// void AAuraCharacterBase::GetMontages_Implementation(TMap<FGameplayTag, UAnimMontage*>& OutMontages)
// {
// 	OutMontages = Montages;
// }

int32 AAuraCharacterBase::GetMinionCount_Implementation()
{
	return MinionCount;
}

void AAuraCharacterBase::IncrementMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);
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
		// 造成伤害的 GE 使用了 Gameplay Effect Execution Calculation（GEEc_Damage），这种 GE 不支持预测！
		// 所以 OnDamaged 只会在服务器上触发！
		AbilitySystemComponent->GetOnDamaged().AddDynamic(this, &ThisClass::ServerHandleDamaged); // 在 Server 上发起 Die
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

// Server
void AAuraCharacterBase::Die()
{
	// GetController()->UnPossess();
	MulticastHandleDeath();
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	
	GetMovementComponent()->Deactivate(); // 先停止移动，不然 Capsule 仍然会有速度

	Weapon->DetachFromComponent(FDetachmentTransformRules{EDetachmentRule::KeepWorld, true});
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetCapsuleComponent()->SetEnableGravity(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	Dissolve();

	bDead = true;
}

FVector AAuraCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	if (MontageTag == FAuraGameplayTags::GetCombatSocketTagWeapon())
	{
		return IsValid(Weapon) ? Weapon->GetSocketLocation(WeaponFireSocketName) : FVector::Zero();
	}
	
	if (MontageTag == FAuraGameplayTags::GetCombatSocketTagLeftHand())
	{
		return GetMesh()->GetSocketLocation(LeftHandDamageSocketName);
	}
	
	if (MontageTag == FAuraGameplayTags::GetCombatSocketTagRightHand())
	{
		return GetMesh()->GetSocketLocation(RightHandDamageSocketName);
	}

	
	if (MontageTag == FAuraGameplayTags::GetCombatSocketTagTail())
	{
		return GetMesh()->GetSocketLocation(TailSocketName);
	}

	return FVector();
}

bool AAuraCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AAuraCharacterBase::GetAvatar_Implementation()
{
	return this;
}

void AAuraCharacterBase::GetMontages_Implementation(TArray<FTaggedMontage>& OutMontages)
{
	OutMontages = Montages;
}

UNiagaraSystem* AAuraCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage AAuraCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	const auto FoundPtr = Montages.FindByPredicate([MontageTag](const FTaggedMontage& Item) { return Item.MontageTag == MontageTag; });
	return FoundPtr ? *FoundPtr : FTaggedMontage{};
}

void AAuraCharacterBase::ShowFloatingDamage(float Damage, const FGameplayEffectContextHandle& EffectContextHandle)
{
	INVALID_RETURN_VOID(FloatingDamageComponentClass);

	const bool bBlockedHit = UAuraAbilitySystemLibrary::IsBlockedHit(EffectContextHandle);
	const bool bCriticalHit = UAuraAbilitySystemLibrary::IsCriticalHit(EffectContextHandle);

	UFloatingDamageComponent* FloatingDamageComponent = NewObject<UFloatingDamageComponent>(this, FloatingDamageComponentClass);
	FloatingDamageComponent->RegisterComponent();

	FloatingDamageComponent->SetDamage(Damage, bBlockedHit, bCriticalHit);
	FloatingDamageComponent->SetRelativeTransform(GetRootComponent()->GetRelativeTransform());

	// FloatingDamageComponent->SetWorldTransform(GetActorTransform() + GetRootComponent()->GetRelativeTransform());
}

void AAuraCharacterBase::ServerHandleDamaged(float Damage, float OldHealth, float NewHealth, const FGameplayEffectContextHandle EffectContextHandle)
{
	if (NewHealth == 0)
	{
		Die(); // 死亡只在服务器判定
	}
	else
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer{FAuraGameplayTags::GetEffectTagHitReact()});
	}

	HandleDamagedCosmetic(Damage, OldHealth, NewHealth, EffectContextHandle);
}

void AAuraCharacterBase::HandleDamagedCosmetic_Implementation(float Damage, float OldHealth, float NewHealth,
                                                              const FGameplayEffectContextHandle EffectContextHandle)
{
	ShowFloatingDamage(Damage, EffectContextHandle);
}

void AAuraCharacterBase::Dissolve()
{
	TArray<UMaterialInstanceDynamic*> DynamicMaterials;

	VALID_THEN_THAT(DissolveMaterialInstance,
	                DynamicMaterials.Add(SetDynamicDissolveMaterial(GetMesh(), DissolveMaterialInstance));
	)

	VALID_THEN_THAT(WeaponDissolveMaterialInstance,
	                DynamicMaterials.Add(SetDynamicDissolveMaterial(Weapon, WeaponDissolveMaterialInstance));
	                StartDissolveTimeline(DynamicMaterials);
	)
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
