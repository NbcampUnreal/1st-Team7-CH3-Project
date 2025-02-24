#include "AI/Task/CP_BTTLookAtPlayerTeam.h"

#include "Cyberpunk.h"
#include "Character/CP_Enemy.h"

#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UCP_BTTLookAtPlayerTeam::UCP_BTTLookAtPlayerTeam()
{
}

EBTNodeResult::Type UCP_BTTLookAtPlayerTeam::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();
	ACP_Enemy* Enemy = Cast<ACP_Enemy>(Controller->GetPawn());
	if (Enemy == nullptr)
	{
		CP_LOG(Warning, TEXT("Enemy == nullptr, Name : %s"), *Controller->GetPawn()->GetName());
		return EBTNodeResult::Failed;
	}

	ACP_CharacterBase* PlayerTeamCharacter = Cast<ACP_CharacterBase>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetPlayer")));
	if (PlayerTeamCharacter == nullptr)
	{
		CP_LOG(Warning, TEXT("PlayerTeamCharacter == nullptr - Fail to get Blackboard Value"));
		return EBTNodeResult::Failed;
	}

	FVector StartPosition = Enemy->GetActorLocation();
	StartPosition.Z = 0;

	FVector EndPosition = PlayerTeamCharacter->GetActorLocation();
	EndPosition.Z = 0;

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartPosition, EndPosition);

	Enemy->SetActorRotation(LookAtRotation);

	return EBTNodeResult::Succeeded;
}
