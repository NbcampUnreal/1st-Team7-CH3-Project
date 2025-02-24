#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CP_BTTLookAtPlayerTeam.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTLookAtPlayerTeam : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UCP_BTTLookAtPlayerTeam();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
