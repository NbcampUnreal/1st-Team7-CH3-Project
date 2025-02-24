#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/CP_AIControllerBase.h"

#include "CP_EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_EnemyAIController : public ACP_AIControllerBase
{
	GENERATED_BODY()

public:

	ACP_EnemyAIController();

protected:

	virtual void OnPossess(APawn* InPawn) override;
};
