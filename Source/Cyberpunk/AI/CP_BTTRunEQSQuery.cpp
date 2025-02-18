#include "AI/CP_BTTRunEQSQuery.h"

#include "Cyberpunk.h"

UCP_BTTRunEQSQuery::UCP_BTTRunEQSQuery()
{
	bNotifyTick = true;
}

void UCP_BTTRunEQSQuery::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (ElapsedTime < FailureTime)
	{
		ElapsedTime += DeltaSeconds;
		return;
	}

	ElapsedTime = 0;

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
}
