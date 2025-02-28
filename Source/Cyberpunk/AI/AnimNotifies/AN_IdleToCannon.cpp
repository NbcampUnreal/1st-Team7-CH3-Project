#include "AI/AnimNotifies/AN_IdleToCannon.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

UAN_IdleToCannon::UAN_IdleToCannon()
{
}

void UAN_IdleToCannon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(MeshComp->GetOwner());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return;
	}

	Boss->SetReturnedToIdle(false);
}
