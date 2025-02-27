#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CP_BTDIsDead.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTDIsDead : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UCP_BTDIsDead();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
