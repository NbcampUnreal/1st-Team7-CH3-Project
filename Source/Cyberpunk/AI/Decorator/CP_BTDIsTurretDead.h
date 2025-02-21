#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CP_BTDIsTurretDead.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTDIsTurretDead : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UCP_BTDIsTurretDead();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
