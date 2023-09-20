// Copyright Yang Dong


#include "Character/AuraCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Character/AuraCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"  // Rider bug
#include "Data/AuraCharacterInfo.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Game/AuraGameStateBase.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Data/AuraGameplayTags.h"

AAuraCharacterBase::AAuraCharacterBase(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer.SetDefaultSubobjectClass(CharacterMovementComponentName, UAuraCharacterMovementComponent::StaticClass()))
{
    PrimaryActorTick.bCanEverTick = false;
    bCanAffectNavigationGeneration = true;

    Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
    Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
    Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

FVector AAuraCharacterBase::GetWeaponFireSocketLocation()
{
    check(Weapon);
    return Weapon->GetSocketLocation(WeaponFireSocketName);
}

void AAuraCharacterBase::HandleDamaged(float Damage, float OldHealth, float NewHealth)
{
    TRUE_RETURN_VOID(NewHealth == 0);

    AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer{FAuraGameplayTags::GetEffectTagHitReact()});
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
    return HitReact;
}