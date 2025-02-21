#include "AI/Decorator/CP_BTDIsAimingPlayer.h"

#include "Character/CP_Turret.h"
#include "Cyberpunk.h"

#include "AIController.h"
#include "Debug/DebugDrawService.h"

UCP_BTDIsAimingPlayer::UCP_BTDIsAimingPlayer()
{
}

bool UCP_BTDIsAimingPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ACP_Turret* Turret = Cast<ACP_Turret>(AIController->GetPawn());
	if (Turret == nullptr)
	{
		CP_LOG(Warning, TEXT("Turret == nullptr"), *AIController->GetPawn()->GetName());
		return false;
	}
	
	FHitResult HitResult;
	FVector StartPoint = Turret->GetActorLocation();
	FVector EndPoint = StartPoint + Turret->GetActorForwardVector() * RecognitionRange;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Turret);

	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, StartPoint, EndPoint, ObjectQueryParams, QueryParams);

	if (bIsHit)
	{
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, false, 3);
	}
	else
	{
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1);
	}

	return bIsHit;
}
