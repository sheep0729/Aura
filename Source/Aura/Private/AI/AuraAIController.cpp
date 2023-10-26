// Copyright Yang Dong


#include "AI/AuraAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


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
}
