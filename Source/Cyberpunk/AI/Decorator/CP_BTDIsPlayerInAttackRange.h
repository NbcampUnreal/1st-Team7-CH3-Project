#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CP_BTDIsPlayerInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTDIsPlayerInAttackRange : public UBTDecorator
{
	GENERATED_BODY()

public:

	UCP_BTDIsPlayerInAttackRange();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
