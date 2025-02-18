#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_RunEQSQuery.h"

#include "CP_BTTRunEQSQuery.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_BTTRunEQSQuery : public UBTTask_RunEQSQuery
{
	GENERATED_BODY()
	
public:

	UCP_BTTRunEQSQuery();

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:


	UPROPERTY(EditAnywhere, Category = "CP")
	float FailureTime = 1;

	float ElapsedTime = 0;
};
