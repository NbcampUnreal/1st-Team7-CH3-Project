#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "CP_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UCP_GameInstance();

protected:

	virtual void Init() override;
};
