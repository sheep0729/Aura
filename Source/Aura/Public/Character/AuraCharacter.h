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
	AAuraCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/* Combat Interface */
	virtual int32 GetActorLevel() override;
	/* Combat Interface */

	AAuraPlayerController* GetAuraPlayerController() const
	{
		return Cast<AAuraPlayerController>(GetController());
	}

	AAuraPlayerController* GetAuraPlayerControllerChecked() const
	{
		return CastChecked<AAuraPlayerController>(GetController());
	}

	virtual void OnRep_Controller() override;

protected:
	virtual void InitAbilitySystemComponent() override;
	virtual void InitHUD() override;

	bool IsAbilityInput(const FGameplayTag& InputTag) const;

private:
	void Move(const FInputActionValue& InputActionValue);
	void ShiftPressed();
	void ShiftReleased();
	void HandleAbilityInput_Pressed(const FGameplayTag InputTag); // 这里的参数不能用引用
	void HandleAbilityInput_Holding(const FGameplayTag InputTag);
	void HandleAbilityInput_Released(const FGameplayTag InputTag);
	void AbortMove();

	UPROPERTY(EditAnywhere, Category="Custom|Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Custom|Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	bool bShiftKeyDown;

	// Click to move

	FVector Destination;
	float ShortPressThreshold;
	float FollowTime;
};
