// Copyright Yang Dong


#include "Actor/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Marco.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/EnemyInterface.h"
#include "Kismet/GameplayStatics.h"

AAuraProjectile::AAuraProjectile()
	: LifeSpan(15),
	  bImpactCosmetic(false),
	  LoopingAudioComponent(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	// bReplicates = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetCollisionProfileName(EAuraCollisionProfileName::Projectile);
	Sphere->SetGenerateOverlapEvents(true);
	SetRootComponent(Sphere);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 550;
	ProjectileMovementComponent->MaxSpeed = 550;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);

	SetLifeSpan(LifeSpan);

	LoopingAudioComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	Sphere->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void AAuraProjectile::Destroyed()
{
	DestroyCosmetic();

	Super::Destroyed();
}

void AAuraProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                bool bFromSweep, const FHitResult& Result)
{
	FALSE_RETURN_VOID(DamageEffectSpecHandle.Data.IsValid());
	const auto EffectCauser = DamageEffectSpecHandle.Data->GetContext().GetEffectCauser();

	// Overlap 无效的目标
	INVALID_RETURN_VOID(OtherActor);

	// Overlap 自己
	TRUE_RETURN_VOID(EffectCauser == OtherActor);

	// Overlap 朋友
	TRUE_RETURN_VOID(UAuraAbilitySystemLibrary::IsFriends(EffectCauser, OtherActor));

	//// Overlap 有效的目标，可能是敌人

	// Overlap 敌人
	if (OtherActor->Implements<UCombatInterface>())
	{
		// TODO 改为 Local Predict ?
		if (HasAuthority())
		{
			if (const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data);
			}
		}
	}

	// Overlap 有效的目标
	UKismetSystemLibrary::PrintString(this, FString::Format(TEXT("Destroying [{0}] {1}"), {GetNameSafe(this), Destroy() ? "Success" : "Failed"}));
}

void AAuraProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                            const FHitResult& Hit)
{
	UKismetSystemLibrary::PrintString(this, FString::Format(TEXT("Destroying [{0}] {1}"), {GetNameSafe(this), Destroy() ? "Success" : "Failed"}));
}

void AAuraProjectile::DestroyCosmetic()
{
	TRUE_RETURN_VOID(bImpactCosmetic);

	bImpactCosmetic = true;

	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), GetActorRotation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation(), GetActorRotation());
	if (IsValid(LoopingAudioComponent)) { LoopingAudioComponent->Stop(); }
}
