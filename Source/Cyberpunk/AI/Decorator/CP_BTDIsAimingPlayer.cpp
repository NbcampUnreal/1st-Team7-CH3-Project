#include "AI/Decorator/CP_BTDIsAimingPlayer.h"

#include "Character/CP_Enemy.h"
#include "Cyberpunk.h"

#include "AIController.h"
#include "Debug/DebugDrawService.h"
#include "Kismet/GameplayStatics.h"

UCP_BTDIsAimingPlayer::UCP_BTDIsAimingPlayer()
{
}

bool UCP_BTDIsAimingPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ACP_Enemy* Enemy = Cast<ACP_Enemy>(AIController->GetPawn());
	if (Enemy == nullptr)
	{
		CP_LOG(Warning, TEXT("Enemy == nullptr"), *AIController->GetPawn()->GetName());
		return false;
	}
	
	FHitResult HitResult;
	FVector StartPoint = Enemy->GetActorLocation();
	FVector EndPoint = StartPoint + Enemy->GetActorForwardVector() * Enemy->GetAttackRange();

	EndPoint.Z = UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation().Z;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Enemy);

	bool bIsHit = GetWorld()->LineTraceSingleByProfile(HitResult, StartPoint, EndPoint, TEXT("Pawn"), QueryParams);//GetWorld()->LineTraceSingleByObjectType(HitResult, StartPoint, EndPoint, ObjectQueryParams, QueryParams);

	if (bIsHit == false)
	{
		//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1);
		return false;
	}

	ACP_CharacterBase* HitCharacter = Cast<ACP_CharacterBase>(HitResult.GetActor());
	if (HitCharacter == nullptr)
	{
		//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1);
		return false;
	}

	bool bIsPlayerTeam = (HitCharacter->GetTeamType() == ETeamType::PlayerTeam) ? true : false;

	if (bIsPlayerTeam)
	{
		//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, false, 3);
	}
	else
	{
		//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1);
	}

	return bIsPlayerTeam;
}
