// Copyright Yang Dong


#include "AI/AuraAIController.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AuraEnemy.h"
#include "Data/AuraCharacterInfo.h"
#include "Data/AuraGameplayTags.h"


// Sets default values
AAuraAIController::AAuraAIController()
{
	bStartAILogicOnPossess = true;

	// 虽然 AI Controller 中也有这两个组件，但蓝图细节不可见
	// 而且 AI Controller 会 FindComponent 来设置它的 Blackboard 和 BrainComponent ，而不是创建，因此在这里 Create 不会导致有多余的组件
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("UBlackboardComponent");
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
}

void AAuraAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto AbilitySystemInterface = Cast<IAbilitySystemInterface>(InPawn))
	{
		if (const auto AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
		{
			AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::GetEffectTagHitReact(), EGameplayTagEventType::NewOrRemoved).AddUObject(
				this,
				&ThisClass::OnHitReactTagChanged
			);
		}
	}

	if (const auto AuraEnemy = Cast<AAuraEnemy>(InPawn))
	{
		GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), AuraEnemy->GetCharacterClass() != EAuraCharacterClass::Warrior);
	}
}

void AAuraAIController::OnHitReactTagChanged(const FGameplayTag Tag, const int32 Count)
{
	const auto AuraEnemy = Cast<AAuraEnemy>(GetPawn());
	INVALID_RETURN_VOID(AuraEnemy);
	
	GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), AuraEnemy->IsHitReacting());
}
