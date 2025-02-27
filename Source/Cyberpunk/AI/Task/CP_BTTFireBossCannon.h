#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CP_BTTFireBossCannon.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTFireBossCannon : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UCP_BTTFireBossCannon();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
