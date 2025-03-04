#include "AI/AnimNotifies/ANS_BossHitWindow.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

UANS_BossHitWindow::UANS_BossHitWindow()
{
}

void UANS_BossHitWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(MeshComp->GetOwner());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return;
	}

	Boss->SetHit(true);
}

void UANS_BossHitWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(MeshComp->GetOwner());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return;
	}

	Boss->SetHit(false);
}
