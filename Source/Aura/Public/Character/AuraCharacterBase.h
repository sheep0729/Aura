// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

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

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

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

	virtual void Die() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

	virtual FVector GetWeaponFireSocketLocation() override;

	UFUNCTION()
	virtual void HandleDamaged(float Damage, float OldHealth, float NewHealth);

	void Dissolve();

	UMaterialInstanceDynamic* SetDynamicDissolveMaterial(USkeletalMeshComponent* InMesh, UMaterialInstance* MaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(const TArray<UMaterialInstanceDynamic*>& MaterialInstanceDynamic);

	UPROPERTY(EditAnywhere, Category="Custom|Class")
	EAuraCharacterClass CharacterClass;

	UPROPERTY(EditAnywhere, Category="Custom|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	UPROPERTY(EditAnywhere, Category="Custom|Combat")
	FName WeaponFireSocketName;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Montage")
	TObjectPtr<UAnimMontage> HitReact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	friend class UAuraAbilitySystemComponent;
};
