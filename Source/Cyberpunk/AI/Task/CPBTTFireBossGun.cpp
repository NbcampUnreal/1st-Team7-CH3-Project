#include "AI/Task/CPBTTFireBossGun.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

#include "AIController.h"

UCPBTTFireBossGun::UCPBTTFireBossGun()
{
}

EBTNodeResult::Type UCPBTTFireBossGun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return EBTNodeResult::Failed;
	}

	Boss->PlayGunFireAnim();

	return EBTNodeResult::Succeeded;
}
