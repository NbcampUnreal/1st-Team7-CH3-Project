#include "AI/Decorator/CP_BTDIsAmingTarget_PlayerTurret.h"

#include "Cyberpunk.h"
#include "Character/CP_PlayerTurret.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCP_BTDIsAmingTarget_PlayerTurret::UCP_BTDIsAmingTarget_PlayerTurret()
{
}

bool UCP_BTDIsAmingTarget_PlayerTurret::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ACP_PlayerTurret* Turret = Cast<ACP_PlayerTurret>(AIController->GetPawn());
	if (Turret == nullptr)
	{
		CP_LOG(Warning, TEXT("Turret == nullptr"));
		return false;
	}

	AActor* Target = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	if (Target == nullptr)
	{
		CP_LOG(Warning, TEXT("Target == nullptr"));
		return false;
	}

	FHitResult HitResult;
	FVector StartPoint = Turret->GetActorLocation();
	FVector EndPoint = StartPoint + Turret->GetActorForwardVector() * Turret->GetAttackRange();
	EndPoint.Z = Target->GetActorLocation().Z;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Turret);

	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, StartPoint, EndPoint, ObjectQueryParams, QueryParams);

	if (bIsHit)
	{
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Blue, false, 3);
	}
	else
	{
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Black, false, 1);
	}

	return bIsHit;
}
