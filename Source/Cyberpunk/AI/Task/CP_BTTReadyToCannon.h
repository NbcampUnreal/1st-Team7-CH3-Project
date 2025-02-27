#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CP_BTTReadyToCannon.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTReadyToCannon : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UCP_BTTReadyToCannon();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
