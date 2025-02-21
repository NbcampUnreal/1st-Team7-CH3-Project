#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CP_BTTTurretRotateToTarget.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTTurretRotateToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UCP_BTTTurretRotateToTarget();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
