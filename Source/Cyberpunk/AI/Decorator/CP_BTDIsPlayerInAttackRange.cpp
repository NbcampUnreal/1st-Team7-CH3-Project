#include "AI/Decorator/CP_BTDIsPlayerInAttackRange.h"

#include "Cyberpunk.h"
#include "Character/CP_Enemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UCP_BTDIsPlayerInAttackRange::UCP_BTDIsPlayerInAttackRange()
{
}

bool UCP_BTDIsPlayerInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
	{
		CP_LOG(Warning, TEXT("PlayerController == nullptr"));
		return false;
	}

	APawn* Player = PlayerController->GetPawn();
	if (Player == nullptr)
	{
		CP_LOG(Warning, TEXT("Player == nullptr"));
		return false;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		CP_LOG(Warning, TEXT("AIController == nullptr"));
		return false;
	}

	ACP_Enemy* Enemy = Cast<ACP_Enemy>(AIController->GetPawn());
	if (Enemy == nullptr)
	{
		CP_LOG(Warning, TEXT("Enemy == nullptr"));
		return false;
	}

	FVector PlayerPosition = Player->GetActorLocation();
	FVector EnemyPosition = Enemy->GetActorLocation();

	float Distance = FVector::Dist(PlayerPosition, EnemyPosition);
	CP_LOG(Warning, TEXT("Attack Range : %f, Distance : %f"), Enemy->GetAttackRange(), Distance);
	return Enemy->GetAttackRange() > Distance;
}
