#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CP_BTTEnemyNormalAttack.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTEnemyNormalAttack : public UBTTaskNode
{
	GENERATED_BODY()
	

public:

	UCP_BTTEnemyNormalAttack();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
