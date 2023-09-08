// Copyright Yang Dong


#include "Character/AuraCharacterBase.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

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
	NULL_RETURN_VOID(GetAuraAbilitySystemComponent());
	
	InitHUD();

	if (HasAuthority())
	{
		InitAttributes(); // 也可以同时在 Client 上初始化，反正是复制的
		InitAbilities();
	}
}

void AAuraCharacterBase::InitAbilitySystemComponent()
{
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
	for (const auto& AttributeEffect : DefaultAttributeEffects)
	{
		ApplyEffectToSelf(AttributeEffect, 1);
	}
}

void AAuraCharacterBase::InitHUD()
{
}

void AAuraCharacterBase::InitAbilities()
{
	for (const auto& Ability : DefaultAbilities)
	{
		AbilitySystemComponent->GiveAbility(Ability, 1);
	}
}
