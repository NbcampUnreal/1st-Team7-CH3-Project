#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CP_BTTAttack_PlayerTurret.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTAttack_PlayerTurret : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UCP_BTTAttack_PlayerTurret();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
