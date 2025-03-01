#include "AI/AnimNotifies/AN_FireBossGun.h"

#include "Cyberpunk.h"
#include "Character/CP_BossEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UAN_FireBossGun::UAN_FireBossGun()
{
}

void UAN_FireBossGun::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACP_BossEnemy* Boss = Cast<ACP_BossEnemy>(MeshComp->GetOwner());
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return;
	}

	AAIController* AIController = Cast<AAIController>(Boss->GetController());
	if (AIController == nullptr)
	{
		CP_LOG(Warning, TEXT("AIController == nullptr"));
		return;
	}

	AActor* Player = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetPlayer")));
	if (Player == nullptr)
	{
		CP_LOG(Warning, TEXT("Player == nullptr"));
		return;
	}

	Boss->FireDirectionalProjectile(Player);
}
