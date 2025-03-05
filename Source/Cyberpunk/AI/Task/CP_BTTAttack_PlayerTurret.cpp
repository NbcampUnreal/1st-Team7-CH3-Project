#include "AI/Task/CP_BTTAttack_PlayerTurret.h"

#include "Cyberpunk.h"
#include "AI/AIController/CP_AIControllerBase.h"
#include "Character/CP_PlayerTurret.h"
#include "BehaviorTree/BlackboardComponent.h"

UCP_BTTAttack_PlayerTurret::UCP_BTTAttack_PlayerTurret()
{
}

EBTNodeResult::Type UCP_BTTAttack_PlayerTurret::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type ResultType = Super::ExecuteTask(OwnerComp, NodeMemory);
	// 임시 공격 로직
	ACP_AIControllerBase* Controller = Cast<ACP_AIControllerBase>(OwnerComp.GetAIOwner());
	if (Controller == nullptr)
	{
		CP_LOG(Warning, TEXT("Controller == nullptr"));
		ResultType = EBTNodeResult::Failed;
		return ResultType;
	}

	ACP_PlayerTurret* Turret = Cast<ACP_PlayerTurret>(Controller->GetPawn());
	if (Turret == nullptr)
	{
		CP_LOG(Warning, TEXT("Turret == nullptr, Controller : %s"), *Controller->GetName());
		ResultType = EBTNodeResult::Failed;
		return ResultType;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	if (Target == nullptr)
	{
		CP_LOG(Warning, TEXT("Target == nullptr"));
		ResultType = EBTNodeResult::Failed;
		return ResultType;
	}

	Turret->Attack(Target);
	ResultType = EBTNodeResult::Succeeded;
	return ResultType;
}
