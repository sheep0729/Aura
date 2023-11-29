// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Marco.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CollisionShape.h"
#include "ANS_CauseDamage.generated.h"

class ADamageVolumeBase;
class IWeaponInterface;
class UCurveTransform;
struct FGameplayTag;
class UCurveVector;
class UAMD_Montage;
struct FCollisionShape;

UCLASS()
class AURA_API UANS_CauseDamage : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CauseDamage)
	FGameplayTag EventTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CauseDamage, meta = (AnimNotifyBoneName = "true"))
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CauseDamage)
	TSubclassOf<AActor> DamageVolumeClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CauseDamage)
	float Interval;
	
	UPROPERTY(EditAnywhere, Category = CauseDamage)
	bool bDrawDebug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CauseDamage)
	bool bRefresh;

	void InitCollisionShape();
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	                         const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	                        const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UFUNCTION(CallInEditor, BlueprintCallable)
	void RefreshMetaData()
	{
		bRefresh = true;
	}

private:
	UPROPERTY()
	UCurveTransform* DamageTransformCurve;

	void SendGameplayEvent(AActor* TargetActor, const TArray<AActor*>& OverlappingActors, const FTransform& DamageTransform);

	void DrawDebug(const UWorld* World, const FTransform& Transform, bool bHit);

	TArray<AActor*> GetOverlappingActors(const USkeletalMeshComponent* MeshComp, const FTransform& DamageTransform);

	float CurrentInterval;

	float TimeElapsed;

	UPROPERTY(Transient)
	TArray<AActor*> ActorsToIgnore;
	
	UPROPERTY(Transient, Instanced)
	ADamageVolumeBase* DamageVolume;

	TOptional<FCollisionShape> CollisionShape;
};
