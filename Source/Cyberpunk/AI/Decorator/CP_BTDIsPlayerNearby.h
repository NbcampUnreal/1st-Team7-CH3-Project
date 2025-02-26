#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CP_BTDIsPlayerNearby.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTDIsPlayerNearby : public UBTDecorator
{
	GENERATED_BODY()

public:

	UCP_BTDIsPlayerNearby();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY(EditAnywhere, Category = "Settings")
	float Distance = 200.0f;
	
};
