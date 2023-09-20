// Copyright Yang Dong


#include "AbilitySystem/Ability/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Data/AuraGameplayTags.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	check(ProjectileClass);

	// TODO: 改为 Local Predict
	// FALSE_RETURN_VOID(GetAvatarActorFromActorInfo()->HasAuthority());

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const auto SocketLocation = CombatInterface->GetWeaponFireSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		// TODO: Set the Projectile Rotation
		const auto Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		const auto SourceASC = GetAbilitySystemComponentFromActorInfo();
		const auto SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

		const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		UKismetSystemLibrary::PrintString(this, FString::Format(TEXT("FireBolt Damage = [{0}]"), {ScaledDamage}));

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FAuraGameplayTags::GetEffectTagDamage(), ScaledDamage);
		Projectile->SetDamageEffectSpecHandle(SpecHandle);

		Projectile->FinishSpawning(SpawnTransform);
	}
}
