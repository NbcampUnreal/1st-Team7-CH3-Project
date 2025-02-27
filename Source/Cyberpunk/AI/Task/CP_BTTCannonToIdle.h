#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CP_BTTCannonToIdle.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTCannonToIdle : public UBTTaskNode
{
	GENERATED_BODY()
	

public:

	UCP_BTTCannonToIdle();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
