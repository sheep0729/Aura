// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Marco.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "AuraWidgetController.generated.h"

class UAuraAbilitySystemComponent;
class AAuraPlayerController;
class AAuraPlayerState;
class UAuraAttributeSet;
class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerActorInfo
{
	GENERATED_BODY()

	void InitFromAbilitySystemComponent(UAbilitySystemComponent* InAbilitySystemComponent)
	{
		AbilitySystemComponent = InAbilitySystemComponent;

		if (!AbilitySystemComponent.IsValid())
		{
			AbilitySystemComponent = nullptr;
			PlayerState = nullptr;
			PlayerController = nullptr;

			return;
		}

		PlayerController = AbilitySystemComponent->AbilityActorInfo->PlayerController;

		for (AActor* TestActor = AbilitySystemComponent->GetOwnerActor(); IsValid(TestActor); TestActor = TestActor->GetOwner())
		{
			if (PlayerState = Cast<APlayerState>(TestActor); PlayerState.IsValid())
			{
				break;
			}
		}
	}

	APlayerController* GetPlayerController()
	{
		return PlayerController.Get();
	}

	APlayerState* GetPlayerState()
	{
		return PlayerState.Get();
	}

	UAbilitySystemComponent* GetAbilitySystemComponent()
	{
		return AbilitySystemComponent.Get();
	}

private:
	UPROPERTY()
	TWeakObjectPtr<APlayerController> PlayerController;

	UPROPERTY()
	TWeakObjectPtr<APlayerState> PlayerState;

	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedSingature, float, NewValue, bool, bInit);


UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();

	void Initialize(UAbilitySystemComponent* AbilitySystemComponent);

	SETTER(WidgetControllerActorInfo);
	CONST_REF_GETTER(WidgetControllerActorInfo);

protected:
	template <typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	virtual void BindCallbacksToDependencies();

	UPROPERTY(BlueprintReadOnly, Category = "Aura|WidgetController")
	FWidgetControllerActorInfo WidgetControllerActorInfo;
};

template <typename T>
T* UAuraWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	if (!IsValid(DataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("[UAuraWidgetController::GetDataTableRowByTag] DataTable 无效"));
		return nullptr;
	}
	return DataTable->FindRow<T>(Tag.GetTagName(), "");
}
