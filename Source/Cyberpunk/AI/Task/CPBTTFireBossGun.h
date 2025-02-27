#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "CPBTTFireBossGun.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCPBTTFireBossGun : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UCPBTTFireBossGun();

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
