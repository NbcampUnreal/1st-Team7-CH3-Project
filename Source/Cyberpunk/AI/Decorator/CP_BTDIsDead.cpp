#include "AI/Decorator/CP_BTDIsDead.h"

#include "Cyberpunk.h"
#include "Character/CP_CharacterBase.h"

#include "AIController.h"

UCP_BTDIsDead::UCP_BTDIsDead()
{
}

bool UCP_BTDIsDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);;

	ACP_CharacterBase* Character = Cast<ACP_CharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr)
	{
		CP_LOG(Warning, TEXT("Character == nullptr, Name : %s"), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
		return false;
	}

	return Character->IsDead();
}
