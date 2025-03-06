#include "AI/Task/CP_BTTLookTarget_PlayerTurret.h"

#include "Character/CP_PlayerTurret.h"
#include "Cyberpunk.h"
#include "Character/CP_Enemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCP_BTTLookTarget_PlayerTurret::UCP_BTTLookTarget_PlayerTurret()
{
	bNotifyTick = false;
}

EBTNodeResult::Type UCP_BTTLookTarget_PlayerTurret::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();

	ACP_PlayerTurret* Turret = Cast<ACP_PlayerTurret>(AIController->GetPawn());
	if (Turret == nullptr)
	{
		CP_LOG(Warning, TEXT("Turret == nullptr, Name : "), *AIController->GetPawn()->GetName());
		return EBTNodeResult::Failed;
	}

	ACP_Enemy* Target = Cast<ACP_Enemy>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (Target == nullptr)
	{
		CP_LOG(Warning, TEXT("Target == nullptr, Name : "), *AIController->GetPawn()->GetName());
		return EBTNodeResult::Failed;
	}

	Turret->AimTarget(Target);
	return EBTNodeResult::Succeeded;
}