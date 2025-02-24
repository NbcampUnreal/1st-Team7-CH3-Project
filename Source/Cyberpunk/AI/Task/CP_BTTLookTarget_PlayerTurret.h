#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CP_BTTLookTarget_PlayerTurret.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTLookTarget_PlayerTurret : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UCP_BTTLookTarget_PlayerTurret();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
