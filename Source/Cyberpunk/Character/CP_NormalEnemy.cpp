#include "CP_NormalEnemy.h"

#include "Debug/DebugDrawService.h"
#include "Cyberpunk.h"
#include "Kismet/GameplayStatics.h"

ACP_NormalEnemy::ACP_NormalEnemy()
{
	AttackRange = 500.0f;
}

void ACP_NormalEnemy::BeginPlay()
{
	Super::BeginPlay();
}

float ACP_NormalEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return NewDamage;
}

void ACP_NormalEnemy::AttackNormal()
{
	Super::AttackNormal();

	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		CP_LOG(Warning, TEXT("World == nullptr"));
		return;
	}

	FHitResult HitResult;
	FVector StartPoint = GetActorLocation();
	FVector EndPoint = StartPoint + GetActorForwardVector() * 100;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel1);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bIsHit = World->LineTraceSingleByObjectType(HitResult, StartPoint, EndPoint, ObjectQueryParams, QueryParams);

	if (bIsHit)
	{
		DrawDebugLine(World, StartPoint, EndPoint, FColor::Green, false, 3);

		UGameplayStatics::ApplyDamage(HitResult.GetActor(), AttackDamage, GetController(), this, nullptr);
	}
	else
	{
		DrawDebugLine(World, StartPoint, EndPoint, FColor::Red, false, 1);
	}
}

void ACP_NormalEnemy::Die()
{
	Super::Die();
}