#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "CP_AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_AIControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:

	ACP_AIControllerBase();

protected:

	virtual void OnPossess(APawn* InPawn) override;
};
