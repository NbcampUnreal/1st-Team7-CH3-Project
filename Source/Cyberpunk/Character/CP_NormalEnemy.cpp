#include "CP_NormalEnemy.h"

#include "Debug/DebugDrawService.h"
#include "Cyberpunk.h"
#include "Kismet/GameplayStatics.h"

ACP_NormalEnemy::ACP_NormalEnemy()
{
	AttackRange = 500.0f;
	Gun = nullptr;
}

void ACP_NormalEnemy::BeginPlay()
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

	Gun->Fire();
}

void ACP_NormalEnemy::Die()
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