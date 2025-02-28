#include "AI/Task/CP_BTTFireBossCannon.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

#include "AIController.h"

UCP_BTTFireBossCannon::UCP_BTTFireBossCannon()
{
}

EBTNodeResult::Type UCP_BTTFireBossCannon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return EBTNodeResult::Failed;
	}

	Boss->PlayCannonFireAnim();

	return EBTNodeResult::Succeeded;
}
