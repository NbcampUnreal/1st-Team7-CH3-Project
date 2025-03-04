#include "Character/CP_CoverEnemy.h"

#include "Cyberpunk.h"

#include "Kismet/GameplayStatics.h"

ACP_CoverEnemy::ACP_CoverEnemy()
{
	Gun = nullptr;
}

void ACP_CoverEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (GunClass)
	{
		Gun = GetWorld()->SpawnActor<ACP_Guns>(GunClass);
		if (Gun)
		{
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Weapon_R"));
			Gun->SetOwner(this);

			// 기본 탄약 설정
			Gun->AmmoCount = 1000;
			Gun->MaxAmmo = 3000;
		}
	}

}

float ACP_CoverEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return NewDamage;
}

void ACP_CoverEnemy::AttackNormal()
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

void ACP_CoverEnemy::Die()
{
	Super::Die();
	if (Gun)
	{
		Gun->Destroy();
		Gun = nullptr;
	}
}
