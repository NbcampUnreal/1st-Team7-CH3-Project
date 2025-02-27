#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "AN_FireBossGun.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UAN_FireBossGun : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	UAN_FireBossGun();

protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
