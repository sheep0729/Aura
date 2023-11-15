// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Marco.h"
#include "AbilitySystem/AuraAbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "GameplayTagContainer.h"
#include "AuraCharacterBase.generated.h"

struct FGameplayTag;
class UWidgetComponent;
class UFloatingDamageComponent;
class UMotionWarpingComponent;
struct FGameplayEffectContext;
struct FGameplayEffectContextHandle;
enum class EAuraCharacterClass : uint8;
class UNavMovementComponent;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAuraAttributeSet;
class UAuraAbilitySystemComponent;
class UAnimMontage;
struct FAuraCharacterInfo;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAuraAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent() const override;

	/* Combat Interface */
	virtual void Die() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void SetFacingTarget_Implementation(const FVector& TargetLocation) override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual void GetMontages_Implementation(TArray<FTaggedMontage>& OutMontages) override;
	/* Combat Interface */

	void ShowFloatingDamage(float Damage, const FGameplayEffectContextHandle& EffectContextHandle);

	VALUE_GETTER(CharacterClass);

protected:
	virtual void BeginPlay() override;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level) const;

	void InitAbilitySystem();

	const FAuraCharacterInfo& GetCharacterInfo() const;

	virtual void InitAbilitySystemComponent();

	virtual void PostInitAbilitySystemComponent();

	virtual void InitAttributes() const;

	virtual void InitUI();

	virtual void InitAbilities();

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

	UFUNCTION()
	virtual void ServerHandleDamaged(float Damage, float OldHealth, float NewHealth, const FGameplayEffectContextHandle EffectContextHandle);
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void HandleDamagedCosmetic(float Damage, float OldHealth, float NewHealth, const FGameplayEffectContextHandle EffectContextHandle);

	void Dissolve();

	UMaterialInstanceDynamic* SetDynamicDissolveMaterial(USkeletalMeshComponent* InMesh, UMaterialInstance* MaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(const TArray<UMaterialInstanceDynamic*>& MaterialInstanceDynamic);

	UPROPERTY(EditAnywhere, Category="Custom|Class", BlueprintReadOnly)
	EAuraCharacterClass CharacterClass;

	UPROPERTY(EditAnywhere, Category="Custom|Combat", BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	// TODO 应该有一个 MontageType
	UPROPERTY(EditAnywhere, Category="Custom|Combat")
	FName WeaponFireSocketName;

	UPROPERTY(EditAnywhere, Category="Custom|Combat")
	FName LeftHandDamageSocketName;

	UPROPERTY(EditAnywhere, Category="Custom|Combat")
	FName RightHandDamageSocketName;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Montage")
	TObjectPtr<UAnimMontage> HitReact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

private:
	bool bDead;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	TSubclassOf<UFloatingDamageComponent> FloatingDamageComponentClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	TArray<FTaggedMontage> Montages;

	friend class UAuraAbilitySystemComponent;
};
