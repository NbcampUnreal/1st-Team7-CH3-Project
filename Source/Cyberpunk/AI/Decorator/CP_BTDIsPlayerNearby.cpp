#include "AI/Decorator/CP_BTDIsPlayerNearby.h"

#include "Cyberpunk.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UCP_BTDIsPlayerNearby::UCP_BTDIsPlayerNearby()
{
}

bool UCP_BTDIsPlayerNearby::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		CP_LOG(Warning, TEXT("AIController == nullptr"));
		return false;
	}

	AActor* Player = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetPlayer")));
	if (Player == nullptr)
	{
		CP_LOG(Warning, TEXT("Player == nullptr"));
		return false;
	}

	APawn* Boss = AIController->GetPawn();
	if (Boss == nullptr)
	{
		CP_LOG(Warning, TEXT("Boss == nullptr"));
		return false;
	}


	float DistanceBetweenPlayer = FVector::Dist(Boss->GetActorLocation(), Player->GetActorLocation());


	return DistanceBetweenPlayer <= Distance;
}
