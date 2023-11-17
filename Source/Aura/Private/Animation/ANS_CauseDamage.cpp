// Copyright Yang Dong


#include "Animation/ANS_CauseDamage.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Curves/CurveVector.h"
#include "Data/AMD_Montage.h"
#include "Kismet/KismetMathLibrary.h"


void UANS_CauseDamage::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	const auto AllMetaData = EventReference.GetNotify()->GetLinkedMontage()->GetMetaData();
	TRUE_RETURN_VOID(AllMetaData.IsEmpty());

	const auto MetaData = Cast<UAMD_Montage>(AllMetaData[0]);
	INVALID_RETURN_VOID(MetaData);

	DamageOrigins = MetaData->GetDamageOrigins();
	INVALID_RETURN_VOID(DamageOrigins);

	if (bRefresh)
	{
		DamageOrigins->ResetCurve();
	}

	ActorsToIgnore.Add(MeshComp->GetOwner());
}

void UANS_CauseDamage::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	INVALID_RETURN_VOID(DamageOrigins);

	CurrentInterval += FrameDeltaTime;
	TimeElapsed += FrameDeltaTime;
	FALSE_RETURN_VOID(CurrentInterval >= Interval);

	FVector SocketLocation;
	if (bRefresh)
	{
		SocketLocation = MeshComp->GetSocketLocation(SocketName);
		for (int i = 0; i < 3; i++)
		{
			DamageOrigins->FloatCurves[i].AddKey(TimeElapsed, SocketLocation[i]);
		}
	}
	else
	{
		SocketLocation = DamageOrigins->GetVectorValue(TimeElapsed);
	}

	CurrentInterval -= Interval;

	const auto Transform = MeshComp->GetComponentTransform();
	const auto DamageOrigin = Transform.TransformPosition(SocketLocation);
	SendGameplayEvent(MeshComp, DamageOrigin);
	DrawDebugSphere(MeshComp->GetWorld(), DamageOrigin, Radius, 16, FColor::White, false, .5);
}

void UANS_CauseDamage::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CurrentInterval = 0;
	TimeElapsed = 0;

	if (bRefresh)
	{
		bRefresh = false;
	}

	ActorsToIgnore.Empty();
}

void UANS_CauseDamage::SendGameplayEvent(const USkeletalMeshComponent* MeshComp, const FVector& DamageOrigin)
{
	const auto OwnerActor = MeshComp->GetOwner();
	const auto Asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor);
	INVALID_RETURN_VOID(Asc);

	TArray<AActor*> OverlappingActor;

	UAuraAbilitySystemLibrary::GetLivePlayerWithinRadius(OwnerActor->GetWorld(), OUT OverlappingActor, ActorsToIgnore, Radius, DamageOrigin);
	TRUE_RETURN_VOID(OverlappingActor.IsEmpty());

	ActorsToIgnore.Append(OverlappingActor); // 每个 Actor 受到一次伤害

	FGameplayEventData EventData;
	EventData.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(OverlappingActor, false);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, EventTag, EventData);
}
