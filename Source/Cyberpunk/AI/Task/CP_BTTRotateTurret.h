#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CP_BTTRotateTurret.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTRotateTurret : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UCP_BTTRotateTurret();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
