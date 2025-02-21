#include "AI/Task/CP_BTTRotateTurret.h"

#include "Cyberpunk.h"

#include "Character/CP_Turret.h"
#include "AIController.h"

UCP_BTTRotateTurret::UCP_BTTRotateTurret()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UCP_BTTRotateTurret::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACP_Turret* Turret = Cast<ACP_Turret>(OwnerComp.GetAIOwner()->GetPawn());
	if (Turret == nullptr)
	{
		CP_LOG(Warning, TEXT("Turret == nullptr, Name : %s "), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
		return EBTNodeResult::Failed;
	}
	
	Turret->SetShouldRotate(true);

	return EBTNodeResult::InProgress;
}

void UCP_BTTRotateTurret::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACP_Turret* Turret = Cast<ACP_Turret>(OwnerComp.GetAIOwner()->GetPawn());
	if (Turret == nullptr)
	{
		CP_LOG(Warning, TEXT("Turret == nullptr, Name : %s "), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
		FinishLatentAbort(OwnerComp);
		return;
	}

	if (Turret->GetShouldRotate() == false)
	{
		CP_LOG(Log, TEXT("Rotate Finished, Name : %s "), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	if (Turret->IsDead())
	{
		CP_LOG(Log, TEXT("Dead.. Rotate Finished, Name : %s "), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	Turret->RotateTurret(Turret->GetRotateSpeed() * DeltaSeconds);
}
