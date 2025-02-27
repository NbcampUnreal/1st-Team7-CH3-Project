#include "AI/Task/CP_BTTCannonToIdle.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

#include "AIController.h"

UCP_BTTCannonToIdle::UCP_BTTCannonToIdle()
{
}

EBTNodeResult::Type UCP_BTTCannonToIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return EBTNodeResult::Failed;
	}

	Boss->SetCannonMode(false);


	return EBTNodeResult::Succeeded;
}
