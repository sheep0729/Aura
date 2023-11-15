// Copyright Yang Dong


#include "Animation/AN_Base.h"

#include "Kismet/KismetSystemLibrary.h"

void UAN_Base::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	// float TriggerTime = EventReference.GetNotify()->TriggerTimeOffset;
	// UKismetSystemLibrary::PrintString(MeshComp, FString::Format(TEXT("{0}"), {TriggerTime}), true);
	Super::Notify(MeshComp, Animation, EventReference);
}
