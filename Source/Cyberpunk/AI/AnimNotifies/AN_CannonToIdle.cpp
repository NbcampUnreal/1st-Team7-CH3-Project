#include "AI/AnimNotifies/AN_CannonToIdle.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

UAN_CannonToIdle::UAN_CannonToIdle()
{
}

void UAN_CannonToIdle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(MeshComp->GetOwner());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return;
	}

	Boss->SetReturnedToIdle(true);
}
