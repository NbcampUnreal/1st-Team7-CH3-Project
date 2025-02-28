#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CP_BTDIsReturnedToIdle.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTDIsReturnedToIdle : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UCP_BTDIsReturnedToIdle();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
