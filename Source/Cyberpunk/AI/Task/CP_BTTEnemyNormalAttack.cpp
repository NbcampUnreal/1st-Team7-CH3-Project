#include "AI/Task/CP_BTTEnemyNormalAttack.h"

#include "Character/CP_Enemy.h"
#include "Cyberpunk.h"
#include "AI/AIController/CP_AIControllerBase.h"

UCP_BTTEnemyNormalAttack::UCP_BTTEnemyNormalAttack()
{
}

EBTNodeResult::Type UCP_BTTEnemyNormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type ResultType = Super::ExecuteTask(OwnerComp, NodeMemory);
	// �ӽ� ���� ����
	ACP_AIControllerBase* Controller = Cast<ACP_AIControllerBase>(OwnerComp.GetAIOwner());
	if (Controller == nullptr)
	{
		CP_LOG(Warning, TEXT("Controller == nullptr"));
		ResultType = EBTNodeResult::Failed;
		return ResultType;
	}
	
	ACP_Enemy* Enemy = Cast<ACP_Enemy>(Controller->GetPawn());
	if (Enemy == nullptr)
	{
		CP_LOG(Warning, TEXT("Enemy == nullptr, Controller : %s"), *Controller->GetName());
		ResultType = EBTNodeResult::Failed;
		return ResultType;
	}

	Enemy->AttackNormal();
	ResultType = EBTNodeResult::Succeeded;
	return ResultType;
}
