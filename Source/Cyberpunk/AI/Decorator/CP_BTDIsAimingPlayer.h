#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "CP_BTDIsAimingPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTDIsAimingPlayer : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UCP_BTDIsAimingPlayer();

protected:
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY(EditAnywhere)
	float RecognitionRange = 500.0f;
};
