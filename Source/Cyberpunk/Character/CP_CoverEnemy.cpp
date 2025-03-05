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

void ACP_CoverEnemy::AttackNormal(AActor* Target)
{
	Super::AttackNormal(Target);

	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		CP_LOG(Warning, TEXT("World == nullptr"));
		return;
	}

	FVector TargetPosition = TargetPosition = Target->GetActorLocation();
	TargetPosition.Z -= 50.0f;

	FVector Direction = TargetPosition - GetActorLocation();
	Direction.Normalize();
	Gun->Fire(Direction);
}

void ACP_CoverEnemy::Die()
{
	FTimerHandle DeadTimerHandle;
	GetWorldTimerManager().SetTimer(DeadTimerHandle, [&]()
		{
			if (::IsValid(this) && ::IsValid(GetWorld()))
			{
				if (Gun)
				{
					Gun->Destroy();
					Gun = nullptr;
				}
			}

		}, 2.5f, false);

	Super::Die();
}
