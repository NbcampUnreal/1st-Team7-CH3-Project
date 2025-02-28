#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"

#include "ANS_BossHitWindow.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UANS_BossHitWindow : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	UANS_BossHitWindow();

protected:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	
};
