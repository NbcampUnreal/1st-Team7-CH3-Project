#include "AI/Task/CP_BTTReadyToCannon.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

#include "AIController.h"

UCP_BTTReadyToCannon::UCP_BTTReadyToCannon()
{
}

EBTNodeResult::Type UCP_BTTReadyToCannon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return EBTNodeResult::Failed;
	}

	Boss->SetCannonMode(true);

	return EBTNodeResult::Succeeded;
}
