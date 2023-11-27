// Copyright Yang Dong


#include "Animation/ANS_CauseDamage.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Data/AMD_Montage.h"
#include "Data/CurveTransform.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CollisionShape.h"
#include "Actor/DamageVolume/DamageVolumeBase.h"


void UANS_CauseDamage::InitCollisionShape()
{
	if (IsValid(DamageVolume))
	{
		CollisionShape = DamageVolume->GetCollisionShape();
	}
}

void UANS_CauseDamage::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	const auto AllMetaData = EventReference.GetNotify()->GetLinkedMontage()->GetMetaData();
	TRUE_RETURN_VOID(AllMetaData.IsEmpty());

	const auto MetaData = Cast<UAMD_Montage>(AllMetaData[0]);
	INVALID_RETURN_VOID(MetaData);

	DamageTransformCurve = MetaData->GetDamageTransform();
	INVALID_RETURN_VOID(DamageTransformCurve);

	INVALID_RETURN_VOID(DamageVolumeClass);
	DamageVolume = Cast<ADamageVolumeBase>(DamageVolumeClass.GetDefaultObject());
	
	InitCollisionShape();

	ActorsToIgnore.Add(MeshComp->GetOwner());

	if (bRefresh)
	{
		DamageTransformCurve->Clear();
	}
}

void UANS_CauseDamage::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	INVALID_RETURN_VOID(DamageTransformCurve);

	CurrentInterval += FrameDeltaTime;
	TimeElapsed += FrameDeltaTime;
	FALSE_RETURN_VOID(CurrentInterval >= Interval);

	FTransform DamageTransform;
	if (bRefresh)
	{
		DamageTransform = MeshComp->GetSocketTransform(SocketName);
		// 注意：先应用的 Transform 应该放在右边
		DamageTransform = DamageVolume->GetCollisionShapeRelativeTransform() * DamageTransform;

		DamageTransformCurve->SetTransform(TimeElapsed, DamageTransform);
	}
	else
	{
		DamageTransform = DamageTransformCurve->GetTransform(TimeElapsed);
	}

	CurrentInterval -= Interval;

	const auto MeshTransform = MeshComp->GetComponentTransform();
	DamageTransform = DamageTransform * MeshTransform;
	const auto OverlappingActors = GetOverlappingActors(MeshComp, DamageTransform);

	if (!bRefresh)
	{
		SendGameplayEvent(MeshComp->GetOwner(), OverlappingActors, DamageTransform);
	}
}

void UANS_CauseDamage::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CurrentInterval = 0;
	TimeElapsed = 0;
	CollisionShape.Reset();
	ActorsToIgnore.Reset();
	DamageTransformCurve = nullptr;
	DamageVolume = nullptr;


	if (bRefresh)
	{
		bRefresh = false;
	}

	ActorsToIgnore.Empty();
}

void UANS_CauseDamage::SendGameplayEvent(AActor* TargetActor, const TArray<AActor*>& OverlappingActors, const FTransform& DamageTransform)
{
	const auto Asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	INVALID_RETURN_VOID(Asc);

	FGameplayEventData EventData;
	EventData.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(OverlappingActors, false);

	FGameplayAbilityTargetData_LocationInfo* TargetLocation = new FGameplayAbilityTargetData_LocationInfo();
	TargetLocation->TargetLocation.LiteralTransform = DamageTransform;
	EventData.TargetData.Add(TargetLocation);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, EventTag, EventData);
}

void UANS_CauseDamage::DrawDebug(const UWorld* World, const FTransform& Transform)
{
	FALSE_RETURN_VOID(bDrawDebug);
	FALSE_RETURN_VOID(CollisionShape.IsSet());

	if (CollisionShape->IsBox())
	{
		UKismetSystemLibrary::DrawDebugBox(World, Transform.GetTranslation(), CollisionShape->GetExtent(), FLinearColor::Blue,
		                                   Transform.GetRotation().Rotator(), .5, 1);
	}
	else if (CollisionShape->IsCapsule())
	{
		UKismetSystemLibrary::DrawDebugCapsule(World, Transform.GetTranslation(), CollisionShape->GetCapsuleHalfHeight(),
		                                       CollisionShape->GetCapsuleRadius(), Transform.GetRotation().Rotator(), FLinearColor::Blue, .5, 1);
	}
	else if (CollisionShape->IsSphere())
	{
		UKismetSystemLibrary::DrawDebugSphere(World, Transform.GetTranslation(), CollisionShape->GetSphereRadius(), 16, FLinearColor::Blue, .5, 1);
	}
}

TArray<AActor*> UANS_CauseDamage::GetOverlappingActors(const USkeletalMeshComponent* MeshComp, const FTransform& DamageTransform)
{
	TArray<AActor*> OverlappingActors;
	FALSE_RETURN_OBJECT(CollisionShape.IsSet(), OverlappingActors);
	
	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActors(ActorsToIgnore);
	
	// TODO 这里可以改成 By Channel、这里应该检查 CollisionShape
	MeshComp->GetWorld()->OverlapMultiByObjectType(Overlaps, DamageTransform.GetTranslation(), DamageTransform.GetRotation(),
	                                               FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),
	                                               CollisionShape.GetValue(), CollisionQueryParams);

	if (bDrawDebug)
	{
		DrawDebug(MeshComp->GetWorld(), DamageTransform);
	}

	for (FOverlapResult& Overlap : Overlaps)
	{
		if (const auto OverlappingActor = Overlap.GetActor(); OverlappingActor && OverlappingActor->Implements<UCombatInterface>())
		{
			if (!ICombatInterface::Execute_IsDead(OverlappingActor))
			{
				OverlappingActors.AddUnique(OverlappingActor);
			}
		}
	}

	ActorsToIgnore.Append(OverlappingActors); // 每个 Actor 受到一次伤害

	return OverlappingActors;
}
