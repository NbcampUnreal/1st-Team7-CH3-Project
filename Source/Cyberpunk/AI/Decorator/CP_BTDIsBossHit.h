#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CP_BTDIsBossHit.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTDIsBossHit : public UBTDecorator
{
	GENERATED_BODY()
	

public:

	UCP_BTDIsBossHit();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
