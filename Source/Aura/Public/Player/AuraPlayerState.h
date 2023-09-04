// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Marco.h"
#include "AbilitySystem/AuraAbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAuraAttributeSet;
class UAuraAbilitySystemComponent;

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAuraAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent() const override;

	VALUE_GETTER(ActorLevel);

protected:
	UPROPERTY(VisibleAnywhere)  // Actor Component 的复制是在构造函数中指定的，这里不需要 Replicated
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	// ASC 中有一个属性是 TArray<FAttributeDefaults> DefaultStartingData;
	// 它可以指定 ASC 中的 AS 的默认值，在 OnRegister() 中会 GetOrCreate 一个 AS ，并添加到 SpawnedAttributes 中。
	//
	// 在 ASC 的 InitializeComponent() 中，会查找它的 Owner 身上的所有 AS ，并 AddUnique 到 SpawnedAttributes 中。
	// OnRegister() 和 InitializeComponent() 都在 UActorComponent::RegisterComponentWithWorld 中调用，但是先调用 OnRegister 。
	//
	// 又由于 SpawnedAttributes 中不同类型的 AS 只能有一个，所以如果设置了 DefaultStartingData ，那么在 InitializeComponent() 时就无法添加 Owner 的 AS 了。
	// 解决方案：不在 Owner 中设置 AttributeSet 。
private:
	UFUNCTION()
	void OnRep_ActorLevel(int32 OldLevel);
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_ActorLevel, Category = "Aura")
	int32 ActorLevel;
};
