#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CPBTDIsCannonMode.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCPBTDIsCannonMode : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UCPBTDIsCannonMode();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
