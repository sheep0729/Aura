// Copyright Yang Dong


#include "AbilitySystem/Ability/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Data/AuraGameplayTags.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	check(ProjectileClass);

	const auto AvatarActor = GetAvatarActorFromActorInfo();
	INVALID_RETURN_VOID(AvatarActor);
	
	// TODO: 预测
	FALSE_RETURN_VOID(AvatarActor->HasAuthority());
	FALSE_RETURN_VOID(AvatarActor->Implements<UCombatInterface>());

	// ICombatInterface::GetCombatSocketLocation() in CombatInterface.gen.cpp:
	// Do not directly call Event functions in Interfaces. Call Execute_GetCombatSocketLocation instead.
	const auto SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(AvatarActor, FAuraGameplayTags::GetMontageTagAttackWeapon()); 
	const FRotator Direction = (ProjectileTargetLocation - SocketLocation).Rotation();

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Direction.Quaternion());

	// TODO: Set the Projectile Rotation
	const auto Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	const auto SourceASC = GetAbilitySystemComponentFromActorInfo();
	const auto EffectContext = SourceASC->MakeEffectContext();
	const auto SpecHandle = SourceASC->MakeOutgoingSpec(GetDamageEffectClass(), GetAbilityLevel(), EffectContext);

	for (auto& DamagePair : GetDamageMap())
	{
		const float ScaledDamage = DamagePair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamagePair.Key, ScaledDamage);
	}

	Projectile->SetDamageEffectSpecHandle(SpecHandle);

	Projectile->FinishSpawning(SpawnTransform);
}
