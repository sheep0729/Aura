// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Marco.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_CauseDamage.generated.h"

struct FGameplayTag;
class UCurveVector;
class UAMD_Montage;
/**
 * 
 */
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
	float Radius;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CauseDamage)
	float Interval;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	                         const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	                        const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = CauseDamage, Transient)
	bool bRefresh;

private:
	UPROPERTY()
	UCurveVector* DamageOrigins;

	void SendGameplayEvent(const USkeletalMeshComponent* MeshComp, const FVector& DamageOrigin);

	float CurrentInterval;

	float TimeElapsed;

	UPROPERTY(Transient)
	TArray<AActor*> ActorsToIgnore;
};
