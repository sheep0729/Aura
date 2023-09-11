// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Player/AuraPlayerController.h"
#include "AuraCharacter.generated.h"

class AAuraPlayerController;
class UNavigationPath;
class USplineComponent;
struct FGameplayTag;
struct FInputActionValue;
class UAuraInputConfig;
class UInputAction;
class UInputMappingContext;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/* Combat Interface */
	virtual int32 GetActorLevel() override;
	/* Combat Interface */
protected:
	virtual void InitAbilitySystemComponent() override;
	virtual void InitHUD() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void HandleAbilityInput_Pressed(const FGameplayTag InputTag); // 这里的参数不能用引用
	void HandleAbilityInput_Holding(const FGameplayTag InputTag);
	void HandleAbilityInput_Released(const FGameplayTag InputTag);
	void AutoMove();

	UPROPERTY(EditAnywhere, Category="Aura|Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Aura|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	// Click to move

	FVector AutoMovementDestination;
	float FollowTime;
	float ShortPressThreshold;
	bool bAutoMoving;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USplineComponent> Spline;
};
