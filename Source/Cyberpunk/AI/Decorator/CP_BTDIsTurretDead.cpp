#include "AI/Decorator/CP_BTDIsTurretDead.h"

#include "Character/CP_Turret.h"
#include "Cyberpunk.h"

#include "AIController.h"

UCP_BTDIsTurretDead::UCP_BTDIsTurretDead()
{
}

bool UCP_BTDIsTurretDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);;

	ACP_Turret* Turret = Cast<ACP_Turret>(OwnerComp.GetAIOwner()->GetPawn());
	if (Turret == nullptr)
	{
		CP_LOG(Warning, TEXT("Turret == nullptr, Name : %s"), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
		return false;
	}

	return Turret->IsDead();
}
