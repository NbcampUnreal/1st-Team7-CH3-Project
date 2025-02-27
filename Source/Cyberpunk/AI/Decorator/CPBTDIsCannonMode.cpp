#include "AI/Decorator/CPBTDIsCannonMode.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

#include "AIController.h"

UCPBTDIsCannonMode::UCPBTDIsCannonMode()
{
}

bool UCPBTDIsCannonMode::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);;

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr, Name : %s"), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
		return false;
	}

	return Boss->IsCannonMode();
}