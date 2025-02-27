#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CP_BTDIsBossFiring.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTDIsBossFiring : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UCP_BTDIsBossFiring();

public:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
