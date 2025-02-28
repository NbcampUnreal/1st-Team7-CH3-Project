#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "AN_CannonToIdle.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UAN_CannonToIdle : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	UAN_CannonToIdle();

protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
