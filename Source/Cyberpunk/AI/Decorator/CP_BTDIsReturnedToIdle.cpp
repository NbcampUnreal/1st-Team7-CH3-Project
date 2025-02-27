#include "AI/Decorator/CP_BTDIsReturnedToIdle.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

#include "AIController.h"

UCP_BTDIsReturnedToIdle::UCP_BTDIsReturnedToIdle()
{
}

bool UCP_BTDIsReturnedToIdle::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return false;
	}

	return Boss->IsReturnedToIdle();
}
