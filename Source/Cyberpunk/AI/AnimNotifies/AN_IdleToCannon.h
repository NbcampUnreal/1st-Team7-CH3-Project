#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "AN_IdleToCannon.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UAN_IdleToCannon : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	UAN_IdleToCannon();

protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
