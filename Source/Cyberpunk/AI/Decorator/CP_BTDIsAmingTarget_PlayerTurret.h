#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CP_BTDIsAmingTarget_PlayerTurret.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTDIsAmingTarget_PlayerTurret : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UCP_BTDIsAmingTarget_PlayerTurret();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
