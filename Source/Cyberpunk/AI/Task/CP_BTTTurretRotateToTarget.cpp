#include "AI/Task/CP_BTTTurretRotateToTarget.h"

#include "Cyberpunk.h"
#include "Character/CP_Turret.h"
#include "Character/CP_Player.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCP_BTTTurretRotateToTarget::UCP_BTTTurretRotateToTarget()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UCP_BTTTurretRotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CP_LOG(Warning, TEXT("Execute"));
	return EBTNodeResult::InProgress;
}

void UCP_BTTTurretRotateToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();

	ACP_Turret* Turret = Cast<ACP_Turret>(AIController->GetPawn());
	if (Turret == nullptr)
	{
		CP_LOG(Warning, TEXT("Turret == nullptr, Name : "), *AIController->GetPawn()->GetName());
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	ACP_Player* Player = Cast<ACP_Player>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetPlayer")));
	if (Player == nullptr)
	{
		CP_LOG(Warning, TEXT("Player == nullptr, Name : "), *AIController->GetPawn()->GetName());
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	CP_LOG(Warning, TEXT("Rotating.... Target Name : %s "), *Player->GetName());

	Turret->AimPlayer(Player);

}
