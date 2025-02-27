#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "AN_FireBossCannon.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UAN_FireBossCannon : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	UAN_FireBossCannon();

protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
